
#include "Processor.h"

Define_Module(Processor);

void Processor::initialize()
{
    service_rate_processor_ = par("service_rate");
    p1 = getParentModule()->par("p1");
    p2 = getParentModule()->par("p2");
    p3 = 1 - p1 - p2;
    idle = true;
}

void Processor::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        idle = true;
        double option = uniform(0, 1);
        if (option < p1)
        {
            send(msg, "to_clients");
        }
        else if (p1 <= option && option < p1 + p2)
        {
            send(msg, "to_disk");
        }
        else
        {
            send(msg, "to_web_server");
        }
    }
    else
    {
        //EV << "Received msg" << endl;
        queue_.push(msg);
    }
    if (!queue_.empty() and idle)
    {
        idle = false;
        cMessage *next_msg = queue_.front();
        queue_.pop();
        scheduleAt(simTime() + exponential(1 / service_rate_processor_), next_msg);
    }
}
