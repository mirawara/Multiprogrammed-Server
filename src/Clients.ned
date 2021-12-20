package multiprogrammed_server;

simple Clients
{
    parameters:
        //Number of clients
        int num_clients=default(1);
        
        int timeWindow @unit(s)=default(10s);

        //Signal for the throughput
        @signal[pkt_counter_s];
        @statistic[pkt_counter](source="pkt_counter_s"; record=mean,vector);
        
     gates:
        input client_in;
        output client_out;
}
