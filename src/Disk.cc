#include "Disk.h"

using namespace std;

Define_Module(Disk);

void Disk::initialize()
{
    //Initially the disk is idle
    idle_ = true;

    Nq_disk_=0;

    disk_backlog_=registerSignal("disk_backlog_s");

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
        Nq_disk_=queue_.size();
        EV << Nq_disk_<<endl;
        emit(disk_backlog_,Nq_disk_);
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

void Disk::finish()
{

    while (queue_.size() > 0)
    {
        cancelAndDelete(queue_.front());
        queue_.pop();
    }
}
