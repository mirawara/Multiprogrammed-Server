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

Define_Module(Clients);

void Clients::initialize()
{
    num_clients_=par("num_clients").intValue();
    num_trans_s_=registerSignal("num_trans_s");
    for(int i=0; i<num_clients_;i++){
            cMessage * msg=new cMessage("Request");
            send(msg, "out_client");
    }
}

void Clients::handleMessage(cMessage *msg)
{
    emit(num_trans_s_,1);
    send(msg,"out_client",msg);
}
