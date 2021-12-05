#ifndef __NCLIENTS_SERVER_SIM_WEBSERVER_H_
#define __NCLIENTS_SERVER_SIM_WEBSERVER_H_

#include <omnetpp.h>
#include <queue>

using namespace omnetpp;
using namespace std;

class WebServer : public cSimpleModule
{

protected:
  //Boolean to check if the processor is idle or not
  bool idle_;

  //Service rate of the processor
  double serv_rate_w_;

  //Queue of requests
  queue<cMessage *> queue_;

  virtual void initialize();
  virtual void handleMessage(cMessage *msg);
};

#endif
