#include "Disk.h"

using namespace std;

Define_Module(Disk);

void Disk::initialize() {
    //Initially the disk is idle
    idle_ = true;

    count_=0;
    Nq_disk_ = 0;

    //Retrieving the timer period for the number of queued requests from the NED file
    Nq_window_ = par("Nq_window");

    disk_queued_req_ = registerSignal("disk_queued_req_s");

    //Recover of the service rate from the NED file
    serv_rate_disk_ = par("service_rate");

    timeWindow_ = par("timeWindow");

    pkt_counter_ = registerSignal("pkt_counter_s");

    service_time_ = registerSignal("service_time_s");

    //Scheduling the timer to record the number of queued requests
    cMessage *msg = new cMessage();
    msg->setName("Nq");
    scheduleAt(Nq_window_, msg);

    //Scheduling the timer to record the number of completed requests
    cMessage *msg_thput = new cMessage();
    msg_thput->setName("Throughput");
    scheduleAt(Nq_window_, msg_thput);
}

void Disk::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage() and strcmp(msg->getName(), "Nq") != 0
        and strcmp(msg->getName(), "Throughput") != 0) {

        //The disk has finished processing the request
        idle_ = true;
        count_++;
        send(msg, "to_processor");
    } else if (msg->isSelfMessage() and strcmp(msg->getName(), "Nq") == 0) {

        //It's the timer for recording the number of queued requests
        Nq_disk_ = queue_.size();
        emit(disk_queued_req_, Nq_disk_);
        scheduleAt(simTime() + Nq_window_, msg);

    } else if (msg->isSelfMessage()
               and strcmp(msg->getName(), "Throughput") == 0) {

        //It's the timer for recording the number of completed requests
        emit(pkt_counter_, count_);
        count_ = 0;
        scheduleAt(simTime() + timeWindow_, msg);
    } else {

        //If it isn't a self message => the request is queued
        queue_.push(msg);

    }
    if (!queue_.empty() and idle_) {
        //If the queue isn't empty and the disk is idle,
        //it takes the first request in the queue
        //and processes it

        //=> The disk is no longer idle
        idle_ = false;

        cMessage *next_msg = queue_.front();

        //Removal of the request from the queue
        queue_.pop();

        //next_msg->setName("processing");
        //Exponential service rate => exponential(mean) (in Omnet++)
        next_service_time_ = exponential(1 / serv_rate_disk_);
        emit(service_time_, next_service_time_);
        scheduleAt(simTime() + next_service_time_, next_msg);
    }
}

void Disk::finish() {

    while (queue_.size() > 0) {
        cMessage *msg = queue_.front();
        delete (msg);
        queue_.pop();
    }
}
