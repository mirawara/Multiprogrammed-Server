

#ifndef __MULTIPROGRAMMED_SERVER_WEBSERVER_H_
#define __MULTIPROGRAMMED_SERVER_WEBSERVER_H_

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

  simsignal_t wserver_backlog_;

  int Nq_wserver_;

  virtual void initialize();
  virtual void handleMessage(cMessage *msg);
  virtual void finish();

};

#endif
