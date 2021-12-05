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

    throughput_ = registerSignal("throughput_s");

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
}

void Clients::handleMessage(cMessage *msg)
{
    //Increase of the counter
    count_ += 1;

    //int client_id = atoi(msg->getName());
    //simtime_t service_time = simTime() - last_request_time[0];
    //emit(service_rate_, 1/service_time);

    emit(throughput_, count_ / simTime());

    //EV << count_ << endl;
    //last_request_time[0] = simTime();

    send(msg, "client_out");
}
