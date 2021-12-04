
#include "WebServer.h"

Define_Module(WebServer);

void WebServer::initialize()
{
    idle=true;
    serv_rate_w_ = par("serv_rate_w").doubleValue();
}

void WebServer::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
        idle=true;
        send(msg, "web_out");
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
        scheduleAt(simTime() + exponential(1/serv_rate_w_), next_msg);
    }
}
