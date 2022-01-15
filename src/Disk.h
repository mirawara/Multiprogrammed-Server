

#ifndef __MULTIPROGRAMMED_SERVER_DISK_H_
#define __MULTIPROGRAMMED_SERVER_DISK_H_

#include <omnetpp.h>
#include <queue>

using namespace omnetpp;
using namespace std;

class Disk : public cSimpleModule {
protected:
    //Boolean to check if the disk is idle or not
    bool idle_;

    //Service rate of the disk
    double serv_rate_disk_;

    //Queue of requests
    queue<cMessage *> queue_;

    //Number of queued requests
    int Nq_disk_;

    //Timer period for the observation of the number of queued requests
    simtime_t Nq_window_;

    simsignal_t disk_queued_req_;

    //Signal for the throughput
    simsignal_t pkt_counter_;

    simsignal_t service_time_;

    simtime_t next_service_time_;

    //Time window in which the number of completed requests is counted
    simtime_t timeWindow_;

    //Counter for completed requests
    int count_;

    virtual void initialize();

    virtual void handleMessage(cMessage *msg);

    virtual void finish();
};

#endif
