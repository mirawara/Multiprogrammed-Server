

#ifndef __MULTIPROGRAMMED_SERVER_WEBSERVER_H_
#define __MULTIPROGRAMMED_SERVER_WEBSERVER_H_

#include <omnetpp.h>
#include <queue>

using namespace omnetpp;
using namespace std;

class WebServer : public cSimpleModule {

protected:
    //Boolean to check if the processor is idle or not
    bool idle_;

    //Service rate of the processor
    double serv_rate_w_;

    //Queue of requests
    queue<cMessage *> queue_;

    //Signal for the number of queued requests
    simsignal_t wserver_queued_req_;

    //Signal for the throughput
    simsignal_t pkt_counter_;

    //Time window in which the number of completed requests is counted
    simtime_t timeWindow_;

    simsignal_t service_time_;

    simtime_t next_service_time_;

    //Number of queued requests
    int Nq_wserver_;

    //Timer period for the evaluation of the number of queued requests
    simtime_t Nq_window_;

    //Counter for completed requests
    int count_;

    virtual void initialize();

    virtual void handleMessage(cMessage *msg);

    virtual void finish();

};

#endif
