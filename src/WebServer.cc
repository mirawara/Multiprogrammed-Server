#include "WebServer.h"

Define_Module(WebServer);

void WebServer::initialize()
{
    //Initially the web serber is idle
    idle_ = true;

    Nq_window_=par("Nq_window");

    wserver_backlog_=registerSignal("wserver_backlog_s");

    //Recover of the service rate from the NED file
    serv_rate_w_ = par("serv_rate_w").doubleValue();

    Nq_wserver_=0;

    cMessage *msg=new cMessage();
    msg->setName("Nq");
    scheduleAt(Nq_window_,msg);
}

void WebServer::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage() and strcmp(msg->getName(),"processing")==0)
    {
        //If it's a self message => the web server has finished processing the request
        idle_ = true;

        send(msg, "web_out");
    }else if(msg->isSelfMessage() and strcmp(msg->getName(),"Nq")==0)
    {
        Nq_wserver_=queue_.size();
        emit(wserver_backlog_,Nq_wserver_);
        scheduleAt(simTime()+Nq_window_,msg);
    }
    else
    {
        //If it isn't a self message => the request is queued
        queue_.push(msg);

    }
    if (!queue_.empty() and idle_)
    {
        //If the queue isn't empty and the web server is idle,
        //it takes the first request in the queue
        //and processes it

        //=> The web server is no longer idle
        idle_ = false;

        cMessage *next_msg = queue_.front();

        //Removal of the request from the queue
        queue_.pop();

        next_msg->setName("processing");

        //Exponential service rate => exponential(mean) (in Omnet++)
        scheduleAt(simTime() + exponential(1 / serv_rate_w_), next_msg);
    }
}

void WebServer::finish()
{

    while (queue_.size() > 0)
    {
        cMessage *msg= queue_.front();
        delete(msg);
        queue_.pop();
    }
}
