
#ifndef __MULTIPROGRAMMED_SERVER_PROCESSOR_H_
#define __MULTIPROGRAMMED_SERVER_PROCESSOR_H_

#include <omnetpp.h>
#include <queue>

using namespace omnetpp;
using namespace std;

class Processor : public cSimpleModule {
protected:
    //Processor's service rate
    double service_rate_processor_;

    //Probability that the transaction is terminated
    //and the reply is sent to the client that originated it
    double p1_;

    //Probability that a disk access is required
    double p2_;

    //Boolean to check if the processor is idle or not
    bool idle_;

    simtime_t Nq_window_;

    //Signal for the throughput
    simsignal_t pkt_counter_;

    //Time window in which the number of completed requests is counted
    simtime_t timeWindow_;

    //Queue of requests
    queue<cMessage *> queue_;

    //Signal for the number of queued requests
    simsignal_t processor_queued_req_;

    simsignal_t service_time_;

    simtime_t next_service_time_;

    //Number of queued requests
    int Nq_processor_;

    //Counter for completed requests
    int count_;

    virtual void initialize();

    virtual void handleMessage(cMessage *msg);

    virtual void finish();
};

#endif
