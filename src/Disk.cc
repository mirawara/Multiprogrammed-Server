#include "Disk.h"

using namespace std;

Define_Module(Disk);

void Disk::initialize()
{
    //Initially the disk is idle
    idle_ = true;

    Nq_disk_=0;

    Nq_window_=par("Nq_window");

    disk_backlog_=registerSignal("disk_backlog_s");

    //Recover of the service rate from the NED file
    serv_rate_disk_ = par("service_rate");

    timeWindow_ = par("timeWindow");

    pkt_counter_ = registerSignal("pkt_counter_s");

    service_time_ = registerSignal("service_time_s");

    cMessage *msg=new cMessage();
    msg->setName("Nq");
    scheduleAt(Nq_window_,msg);

    cMessage *msg_thput=new cMessage();
    msg_thput->setName("Throughput");
    scheduleAt(Nq_window_,msg_thput);
}

void Disk::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage() and strcmp(msg->getName(),"processing")==0)
    {
        //If it's a self message => the disk has finished processing the request
        idle_ = true;
        count_++;

        send(msg, "to_processor");
    }else if(msg->isSelfMessage() and strcmp(msg->getName(),"Nq")==0)
    {
        Nq_disk_=queue_.size();
        emit(disk_backlog_,Nq_disk_);
        scheduleAt(simTime()+Nq_window_,msg);

    }else if(msg->isSelfMessage() and strcmp(msg->getName(),"Throughput")==0)
    {
        emit(pkt_counter_,count_);
        count_=0;
        scheduleAt(simTime()+timeWindow_, msg);
    }else
    {
        //If it isn't a self message => the request is queued
        queue_.push(msg);

    }
    if (!queue_.empty() and idle_)
    {
        //If the queue isn't empty and the disk is idle,
        //it takes the first request in the queue
        //and processes it

        //=> The disk is no longer idle
        idle_ = false;

        cMessage *next_msg = queue_.front();

        //Removal of the request from the queue
        queue_.pop();

        next_msg->setName("processing");
        //Exponential service rate => exponential(mean) (in Omnet++)
        next_service_time_ = exponential(1 / serv_rate_disk_);
        emit(service_time_, next_service_time_);
        scheduleAt(simTime() + next_service_time_, next_msg);
    }
}

void Disk::finish()
{

    while (queue_.size() > 0)
    {
        cMessage *msg= queue_.front();
        delete(msg);
        queue_.pop();
    }
}
