package multiprogrammed_server;

simple Clients
{
    parameters:
        //Number of clients
        int num_clients = default(1);

		//Time window in which the number of completed requests is counted
        int timeWindow @unit(s) = default(10s);

        @signal[interarrival_time_s];
        @statistic[interarrival_time](source="interarrival_time_s"; record=mean,vector);

        @signal[response_time_s];
        @statistic[response_time](source="response_time_s"; record=mean,vector);

        //Signal for the throughput
        @signal[pkt_counter_s];
        @statistic[pkt_counter](source="pkt_counter_s"; record=mean,vector);

    gates:
        input client_in;
        output client_out;
}
