
#ifndef __NCLIENTS_SERVER_SIM_CLIENTS_H_
#define __NCLIENTS_SERVER_SIM_CLIENTS_H_

#include <omnetpp.h>

using namespace omnetpp;

class Clients : public cSimpleModule
{
private:
  //Array used to store the simulation times
  //used to compute the response times for the
  //complete requests for each client
  simtime_t *last_request_time;

protected:
  //Number of Clients
  int num_clients_;

  //Signal of the service rate registration
  simsignal_t service_rate_;
  simsignal_t throughput_;
  int count_;

  virtual void initialize();
  virtual void handleMessage(cMessage *msg);
};

#endif
