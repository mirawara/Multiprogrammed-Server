//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef __MULTIPROGRAMMED_SERVER_PROCESSOR_H_
#define __MULTIPROGRAMMED_SERVER_PROCESSOR_H_

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

  simtime_t Nq_window_;

  //Signal for the throughput
  simsignal_t pkt_counter_;

  simtime_t timeWindow_;

  //Queue of requests
  queue<cMessage *> queue_;

  simsignal_t processor_backlog_;

  simsignal_t service_time_;

  simtime_t next_service_time_;

  int Nq_processor_;

  //Counter for completed requests
   int count_;

  virtual void initialize();
  virtual void handleMessage(cMessage *msg);
  virtual void finish();
};

#endif
