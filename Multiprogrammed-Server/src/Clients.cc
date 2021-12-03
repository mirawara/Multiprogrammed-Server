
#include "Clients.h"

using namespace std;

Define_Module(Clients);

void Clients::initialize()
{

    count_=0;
    //Recover of the number of clients from Clients.ned
    num_clients_ = par("num_clients").intValue();

    //Array used to store the simulation times
    //used to compute the response times for the
    //complete requests for each client
    last_request_time = new simtime_t[num_clients_];

    //Signal of the service rate registration
    service_rate_ = registerSignal("service_rate");

    throughput_=registerSignal("throughput_s");

    //Sending of the N messages to the Server
    for (int i = 0; i < num_clients_; i++)
    {

        //Inizitializing the elements of the array
        last_request_time[i] = 0;

        //Conversion from int to char*
        char i_ = i + '0';
        char *id_client = &i_;

        //EV << *id_client << endl;

        cMessage *msg = new cMessage();

        //set the number of client
        //as the name of the message
        msg->setName(id_client);
        send(msg, "client_out");
    }
}

void Clients::handleMessage(cMessage *msg)
{
    count_ +=1;
    //Conversion from char* to int in order
    //to recover the number of the client
    //used to access the array of request times
    int client_id = atoi(msg->getName());

    //Calculation of the service time by the difference
    //of the actual simulation time and the sending of the request's time
    simtime_t service_time = simTime() - last_request_time[0];
    emit(service_rate_, 1 / service_time);
    emit(throughput_,count_/simTime());

    simtime_t now = simTime();

    EV << now << simTime() << endl;

    //Update of the request time
    last_request_time[0] = simTime();
    send(msg, "client_out");
}
