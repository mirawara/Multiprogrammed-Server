#include "Clients.h"
#include <string>

using namespace std;

Define_Module(Clients);

void Clients::initialize() {
    //last_request_time = new simtime_t[num_clients_];
    //service_rate_ = registerSignal("service_rate");

    //Initialization of the counter
    count_ = 0;

    arrival_time_ = simTime();

    //Recover of the number of clients from Clients.ned
    num_clients_ = par("num_clients").intValue();
    response_times_ = new simtime_t[num_clients_];
    for (int i = 0; i < num_clients_; i++)
        response_times_[i] = 0;

    timeWindow_ = par("timeWindow");

    pkt_counter_ = registerSignal("pkt_counter_s");
    interarrival_time_ = registerSignal("interarrival_time_s");
    response_time_ = registerSignal("response_time_s");

    //Sending of the N messages to the Server
    for (int i = 0; i < num_clients_; i++) {

        cMessage *msg = new cMessage(to_string(i).c_str());

        // msg->setName(id_client);
        send(msg, "client_out");
    }

    cMessage *selfMsg_ = new cMessage();
    scheduleAt(timeWindow_, selfMsg_);
}

void Clients::handleMessage(cMessage *msg) {

    if (msg->isSelfMessage()) {
        emit(pkt_counter_, count_);
        count_ = 0;
        scheduleAt(simTime() + timeWindow_, msg);
    } else {
        count_ += 1;

        emit(interarrival_time_, simTime() - arrival_time_);
        arrival_time_ = simTime();

        int id_client = atoi(msg->getName());

        emit(response_time_, simTime() - response_times_[id_client]);
        response_times_[id_client] = simTime();

        send(msg, "client_out");
    }
}

void Clients::finish() {

    delete[] response_times_;
}
