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

#include "Disk.h"

using namespace std;

Define_Module(Disk);

void Disk::initialize()
{
    serv_rate_disk_ = par("service_rate");
}

void Disk::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()){
        send(msg, "to_processor");
    }else{
        queue_.push(msg);
    }
    cMessage* next=queue_.front();
    double proc_time=1/exponential(serv_rate_disk_);
    scheduleAt( simTime()+proc_time, next);
    queue_.pop();
}
