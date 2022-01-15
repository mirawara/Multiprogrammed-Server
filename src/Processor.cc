#include "Processor.h"
#include "Clients.h"

Define_Module(Processor);

void Processor::initialize() {
    //Recover of the processor's service rate from the NED file
    service_rate_processor_ = par("service_rate");

    Nq_processor_ = 0;

    Nq_window_ = par("Nq_window");

    //Recover of the probabilty p1 from the server compund module
    p1_ = getParentModule()->par("p1");

    //Recover of the probabilty p2 from the server compund module
    p2_ = getParentModule()->par("p2");

    processor_queued_req_ = registerSignal("processor_queued_req_s");

    timeWindow_ = par("timeWindow");

    pkt_counter_ = registerSignal("pkt_counter_s");

    service_time_ = registerSignal("service_time_s");

    //Initially the processor is idle
    idle_ = true;

    //Scheduling the timer for counting the number of queued requests
    cMessage *msg = new cMessage();
    msg->setName("Nq");
    scheduleAt(Nq_window_, msg);

    //Scheduling the timer for counting the number of completed requests
    cMessage *msg_thput = new cMessage();
    msg_thput->setName("Throughput");
    scheduleAt(Nq_window_, msg_thput);
}

void Processor::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage() and strcmp(msg->getName(), "Nq") != 0 and strcmp(msg->getName(), "Throughput") != 0) {

        //the processor has finished processing the request
        idle_ = true;
        count_++;
        //Generation of the random number used to choose
        //the request's path
        double option = uniform(0, 1, 1);

        if (option < p1_) //=> with probability p1
        {
            send(msg, "to_clients");
        } else if (p1_ <= option && option < p1_ + p2_) //=> with probability p2
        {
            send(msg, "to_disk");
        } else //=> with probability p3
        {
            send(msg, "to_web_server");
        }
    } else if (msg->isSelfMessage() and strcmp(msg->getName(), "Nq") == 0) {

        //It's the timer for counting the number of queued requests
        Nq_processor_ = queue_.size();
        emit(processor_queued_req_, Nq_processor_);
        scheduleAt(simTime() + Nq_window_, msg);
    } else if (msg->isSelfMessage() and strcmp(msg->getName(), "Throughput") == 0) {

        //It's the timer for counting the number of completed requests
        emit(pkt_counter_, count_);
        count_ = 0;
        scheduleAt(simTime() + timeWindow_, msg);
    } else {
        //If it isn't a self message => the request is queued
        queue_.push(msg);


    }
    if (!queue_.empty() and idle_) {
        //If the queue isn't empty and the server is idle,
        //it takes the first request in the queue
        //and processes it

        //=> The processor is no longer idle
        idle_ = false;

        cMessage *next_msg = queue_.front();

        //Removal of the request from the queue
        queue_.pop();

        //next_msg->setName("processing");
        //Exponential service rate => exponential(mean) (in Omnet++)
        next_service_time_ = exponential(1 / service_rate_processor_,0);
        emit(service_time_, next_service_time_);
        scheduleAt(simTime() + next_service_time_, next_msg);
    }
}

void Processor::finish() {

    while (queue_.size() > 0) {
        cMessage *msg = queue_.front();
        delete (msg);
        queue_.pop();
    }
}
