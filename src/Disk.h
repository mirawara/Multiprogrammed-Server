#ifndef __NCLIENTS_SERVER_SIM_DISK_H_
#define __NCLIENTS_SERVER_SIM_DISK_H_

#include <omnetpp.h>
#include <queue>

using namespace omnetpp;
using namespace std;

class Disk : public cSimpleModule
{
protected:
  //Boolean to check if the disk is idle or not
  bool idle_;

  //Service rate of the disk
  double serv_rate_disk_;

  //Queue of requests
  queue<cMessage *> queue_;

  int Nq_disk_;

  simsignal_t disk_backlog_;

  virtual void initialize();
  virtual void handleMessage(cMessage *msg);
};

#endif
