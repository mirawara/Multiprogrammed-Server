#ifndef __MULTIPROGRAMMED_SERVER_CLIENTS_H_
#define __MULTIPROGRAMMED_SERVER_CLIENTS_H_

#include <omnetpp.h>

using namespace omnetpp;

class Clients : public cSimpleModule {

protected:
    //Number of Clients
    int num_clients_;

    //Signal for the throughput
    simsignal_t pkt_counter_;

    //Counter for completed requests
    int count_;

    //Time window in which the number of completed requests is counted
    simtime_t timeWindow_;

    //Storing the time of the last arrival of a request to the server
    simtime_t arrival_time_;

    simsignal_t interarrival_time_;

    //Storing the time of the last arrival of a response from the server, for each client
    simtime_t *response_times_;

    simsignal_t response_time_;

    virtual void initialize();

    virtual void handleMessage(cMessage *msg);

    virtual void finish();
};

#endif
