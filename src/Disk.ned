package multiprogrammed_server;

simple Disk
{
    parameters:
        //Service rate of the disk
        double service_rate = default(1);

		//Timer period for the observation of the number of queued requests
        int Nq_window @unit(s) = default(1s);
        //Time window in which the number of completed requests is counted
        int timeWindow @unit(s) = default(10s);

        //Signal for the throughput
        @signal[pkt_counter_s];
        @statistic[pkt_counter_disk](source="pkt_counter_s"; record=mean);

		//Signal for the number of queued requests
        @signal[disk_queued_req_s];
        @statistic[disk_queued_req](source="disk_queued_req_s"; record=vector);

        @signal[service_time_s];
        @statistic[service_time_disk](source="service_time_s"; record=mean);

    gates:
        input from_processor;
        output to_processor;
}
