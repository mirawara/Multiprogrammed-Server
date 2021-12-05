#ifndef __NCLIENTS_SERVER_SIM_PROCESSOR_H_
#define __NCLIENTS_SERVER_SIM_PROCESSOR_H_

#include <omnetpp.h>
#include <queue>

using namespace omnetpp;
using namespace std;

class Processor : public cSimpleModule
{
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

  //Queue of requests
  queue<cMessage *> queue_;

  virtual void initialize();
  virtual void handleMessage(cMessage *msg);
};

#endif
