#include "Clients.h"

using namespace std;

Define_Module(Clients);

void Clients::initialize()
{
    //last_request_time = new simtime_t[num_clients_];
    //service_rate_ = registerSignal("service_rate");

    //Initialization of the counter
    count_ = 0;



    //Recover of the number of clients from Clients.ned
    num_clients_ = par("num_clients").intValue();

    timeWindow_ = par("timeWindow");

    pkt_counter_ = registerSignal("pkt_counter_s");

    //Sending of the N messages to the Server
    for (int i = 0; i < num_clients_; i++)
    {
        //last_request_time[i] = 0;
        //char i_ = i + '0';
        //char *id_client = &i_;

        cMessage *msg = new cMessage();

        //msg->setName(id_client);
        send(msg, "client_out");
    }


    cMessage *selfMsg_=new cMessage();
    scheduleAt(timeWindow_, selfMsg_);
}

void Clients::handleMessage(cMessage *msg)
{
    if(msg->isSelfMessage()){
        emit(pkt_counter_,count_);

        count_=0;
        scheduleAt(simTime()+timeWindow_, msg);
    }else{
        count_ += 1;
        send(msg, "client_out");
    }
}
