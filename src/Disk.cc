
#include "Disk.h"

using namespace std;

Define_Module(Disk);

void Disk::initialize()
{
    idle=true;
    serv_rate_disk_ = par("service_rate");
}

void Disk::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        idle=true;
        send(msg, "to_processor");
    }
    else
    {
        queue_.push(msg);
    }
    if (!queue_.empty() and idle)
    {
        idle=false;
        cMessage *next_msg = queue_.front();
        queue_.pop();
        scheduleAt(simTime() + exponential(1/serv_rate_disk_), next_msg);
    }
}
