#include "Clients.h"
#include <string>

using namespace std;

Define_Module(Clients);

void Clients::initialize()
{
    //Initialization of the counter
    count_ = 0;

    arrival_time_ = simTime();

    //Recover of the number of clients from Clients.ned
    num_clients_ = par("num_clients").intValue();

    //Array storing for each client the last arrival of a response from the server
    response_times_ = new simtime_t[num_clients_];
    for (int i = 0; i < num_clients_; i++)
        response_times_[i] = 0;

    //Retrieving the time window for throughput evaluation
    timeWindow_ = par("timeWindow");

    //Associating each sim_signal_t to the corresponding signal in Clients.ned
    pkt_counter_ = registerSignal("pkt_counter_s");
    interarrival_time_ = registerSignal("interarrival_time_s");
    response_time_ = registerSignal("response_time_s");

    //Sending of the N messages to the Server
    for (int i = 0; i < num_clients_; i++)
    {

        cMessage *msg = new cMessage(to_string(i).c_str());
        send(msg, "client_out");
    }

    //Timer for the evaluation of the number of completed requests
    cMessage *selfMsg_ = new cMessage();
    scheduleAt(timeWindow_, selfMsg_);
}

void Clients::handleMessage(cMessage *msg)
{

    if (msg->isSelfMessage())
    {
        //Recording the number of completed requests in the time window
        emit(pkt_counter_, count_);
        //Resetting the counter
        count_ = 0;
        //Scheduling a new timer event
        scheduleAt(simTime() + timeWindow_, msg);
    }
    else
    {
        //Updating counter of completed requests
        count_ += 1;

        //Recording the interarrival time between two subsequent requests to the server
        emit(interarrival_time_, simTime() - arrival_time_);
        arrival_time_ = simTime();

        //Id of the client receiving the reply
        int id_client = atoi(msg->getName());

        //Recording the response time for this completed request
        emit(response_time_, simTime() - response_times_[id_client]);
        response_times_[id_client] = simTime();

        //Sending a new request to the server
        send(msg, "client_out");
    }
}

void Clients::finish()
{

    delete[] response_times_;
}
