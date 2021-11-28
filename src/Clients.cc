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

#include "Clients.h"

using namespace std;

Define_Module(Clients);

void Clients::initialize()
{
    num_clients_=par("num_clients").intValue();
    last_request_time = new simtime_t[num_clients_];
    service_rate_=registerSignal("service_rate");
    for(int i=0; i<num_clients_;i++){
            last_request_time[i] = 0;
            char i_ = i+'0';
            char* id_client = &i_;
            EV << *id_client << endl;
            cMessage* msg=new cMessage();
            msg->setName(id_client);
            send(msg, "client_out");
    }
}

void Clients::handleMessage(cMessage *msg)
{
    int client_id = atoi(msg->getName());
    simtime_t service_time = simTime() - last_request_time[client_id];
    emit(service_rate_,1/service_time);
    EV << 1/service_time << endl;
    last_request_time[client_id] = simTime();
    send(msg,"client_out");
}
