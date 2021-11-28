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

#include "Processor.h"

Define_Module(Processor);

void Processor::initialize()
{
    service_rate_processor_ = par("service_rate");
    p1 = getParentModule()->par("p1");
    p2 = getParentModule()->par("p2");
    p3 = 1-p1-p2;
}

void Processor::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage())
    {
       double option = uniform(0,1);
       EV << option << endl;
       if (option < p1)
           send(msg, "to_clients");
       else if (p1 <= option && option < p1+p2)
           send(msg, "to_disk");
       else
           send(msg, "to_web_server");
    }
    else
    {
        EV << "Received msg" << endl;
        queue_.push(msg);
    }
    if (!queue_.empty())
    {
        cMessage* next_msg = queue_.front();
        queue_.pop();
        scheduleAt(simTime() + 1/exponential(service_rate_processor_), next_msg);
    }

}
