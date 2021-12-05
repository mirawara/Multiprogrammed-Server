#ifndef __NCLIENTS_SERVER_SIM_CLIENTS_H_
#define __NCLIENTS_SERVER_SIM_CLIENTS_H_

#include <omnetpp.h>

using namespace omnetpp;

class Clients : public cSimpleModule
{

protected:
  //simtime_t *last_request_time;
  //simsignal_t service_rate_;

  //Number of Clients
  int num_clients_;

  //Signal for the throughput
  simsignal_t throughput_;

  //Counter for completed requests
  int count_;

  virtual void initialize();
  virtual void handleMessage(cMessage *msg);
};

#endif
