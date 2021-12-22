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

void WebServer::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage() and strcmp(msg->getName(),"Nq")!=0 and strcmp(msg->getName(), "Throughput")!=0)
    {
        //If it's a self message => the web server has finished processing the request
        idle_ = true;
        count_++;

        send(msg, "web_out");
    }else if(msg->isSelfMessage() and strcmp(msg->getName(),"Nq")==0)
    {
        Nq_wserver_=queue_.size();
        emit(wserver_backlog_,Nq_wserver_);
        scheduleAt(simTime()+Nq_window_,msg);
    }
    else if(msg->isSelfMessage() and strcmp(msg->getName(),"Throughput")==0)
    {
        emit(pkt_counter_,count_);
        count_=0;
        scheduleAt(simTime()+timeWindow_, msg);
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

        //next_msg->setName("processing");

        //Exponential service rate => exponential(mean) (in Omnet++)
        next_service_time_ = exponential(1 / serv_rate_w_);
        emit(service_time_, next_service_time_);
        scheduleAt(simTime() + next_service_time_, next_msg);
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
