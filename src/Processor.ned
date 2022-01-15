package multiprogrammed_server;
simple Processor
{
    parameters:
        //Processor's service rate
        double service_rate = default(1);

		//Timer period for the observation of the number of queued requests
        int Nq_window @unit(s) = default(1s);
        //Time window in which the number of completed requests is counted
        int timeWindow @unit(s) = default(10s);

        //Signal for the throughput
        @signal[pkt_counter_s];
        @statistic[pkt_counter_processor](source="pkt_counter_s"; record=mean);

		//Signal for the number of queued requests
        @signal[processor_queued_req_s];
        @statistic[processor_queued_req](source="processor_queued_req_s"; record=mean,vector);

        @signal[service_time_s];
        @statistic[service_time_processor](source="service_time_s"; record=mean);

    gates:
        input from_clients;
        input from_disk;
        input from_web_server;
        output to_clients;
        output to_disk;
        output to_web_server;
}
