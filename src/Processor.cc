#include "Processor.h"

Define_Module(Processor);

void Processor::initialize()
{
    //Recover of the processor's service rate from the NED file
    service_rate_processor_ = par("service_rate");

    Nq_processor_=0;

    //Recover of the probabilty p1 from the server compund module
    p1_ = getParentModule()->par("p1");

    //Recover of the probabilty p2 from the server compund module
    p2_ = getParentModule()->par("p2");

    processor_backlog_=registerSignal("processor_backlog_s");

    //Initially the processor is idle
    idle_ = true;
}

void Processor::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        //If it's a self message => the processor has finished processing the request
        idle_ = true;

        //Generation of the random number used to choose
        //the request's path
        double option = uniform(0, 1, 1);

        if (option < p1_) //=> with probability p1
        {
            send(msg, "to_clients");
        }
        else if (p1_ <= option && option < p1_ + p2_) //=> with probability p2
        {
            send(msg, "to_disk");
        }
        else //=> with probability p3
        {
            send(msg, "to_web_server");
        }
    }
    else
    {
        //If it isn't a self message => the request is queued
        queue_.push(msg);

        Nq_processor_=queue_.size();
        emit(processor_backlog_,Nq_processor_);
    }
    if (!queue_.empty() and idle_)
    {
        //If the queue isn't empty and the server is idle,
        //it takes the first request in the queue
        //and processes it

        //=> The processor is no longer idle
        idle_ = false;

        cMessage *next_msg = queue_.front();

        //Removal of the request from the queue
        queue_.pop();

        //Exponential service rate => exponential(mean) (in Omnet++)
        scheduleAt(simTime() + exponential(1 / service_rate_processor_,0), next_msg);
    }
}
