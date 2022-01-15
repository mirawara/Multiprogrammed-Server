#include "WebServer.h"

Define_Module(WebServer);

void WebServer::initialize() {
    //Initially the web server is idle
    idle_ = true;

    //Retrieving the timer period for measuring the number of queued requests
    Nq_window_ = par("Nq_window");

    wserver_queued_req_ = registerSignal("wserver_queued_req_s");

    //Recover of the service rate from the NED file
    serv_rate_w_ = par("serv_rate_w").doubleValue();

    Nq_wserver_ = 0;

    //Retrieving the time window in which the number of completed requests is counted
    timeWindow_ = par("timeWindow");

    pkt_counter_ = registerSignal("pkt_counter_s");

    service_time_ = registerSignal("service_time_s");

    //Scheduling the timer in order to count the number of queued requests
    cMessage *msg = new cMessage();
    msg->setName("Nq");
    scheduleAt(Nq_window_, msg);

    //Scheduling the timer in order to count the number of completed requests
    cMessage *msg_thput = new cMessage();
    msg_thput->setName("Throughput");
    scheduleAt(Nq_window_, msg_thput);
}

void WebServer::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage() and strcmp(msg->getName(), "Nq") != 0 and strcmp(msg->getName(), "Throughput") != 0) {

        //the web server has finished processing the request
        idle_ = true;
        count_++;

        send(msg, "web_out");
    } else if (msg->isSelfMessage() and strcmp(msg->getName(), "Nq") == 0) {

        //It's the timer for the number of queued requests
        Nq_wserver_ = queue_.size();
        emit(wserver_queued_req_, Nq_wserver_);
        scheduleAt(simTime() + Nq_window_, msg);
    } else if (msg->isSelfMessage() and strcmp(msg->getName(), "Throughput") == 0) {

        //It's the timer for the number of completed requests
        emit(pkt_counter_, count_);
        count_ = 0;
        scheduleAt(simTime() + timeWindow_, msg);
    } else {

        //If it isn't a self message => the request is queued
        queue_.push(msg);

    }
    if (!queue_.empty() and idle_) {
        //If the queue isn't empty and the web server is idle,
        //it takes the first request in the queue
        //and processes it

        //=> The web server is no longer idle
        idle_ = false;

        cMessage *next_msg = queue_.front();

        //Removal of the request from the queue
        queue_.pop();

        //Exponential service rate => exponential(mean) (in Omnet++)
        next_service_time_ = exponential(1 / serv_rate_w_);
        emit(service_time_, next_service_time_);
        scheduleAt(simTime() + next_service_time_, next_msg);
    }
}

void WebServer::finish() {

    while (queue_.size() > 0) {
        cMessage *msg = queue_.front();
        delete (msg);
        queue_.pop();
    }
}
