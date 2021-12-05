#include "Disk.h"

using namespace std;

Define_Module(Disk);

void Disk::initialize()
{
    //Initially the disk is idle
    idle_ = true;

    //Recover of the service rate from the NED file
    serv_rate_disk_ = par("service_rate");
}

void Disk::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        //If it's a self message => the disk has finished processing the request
        idle_ = true;

        send(msg, "to_processor");
    }
    else
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

        //Exponential service rate => exponential(mean) (in Omnet++)
        scheduleAt(simTime() + exponential(1 / serv_rate_disk_), next_msg);
    }
}
