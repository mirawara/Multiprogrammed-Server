package multiprogrammed_server;

simple Disk
{
    parameters:
        //Service rate of the disk
        double service_rate = default(1);

        int Nq_window @unit(s) = default(1s);
        int timeWindow @unit(s) = default(10s);

        //Signal for the throughput
        @signal[pkt_counter_s];
        @statistic[pkt_counter_disk](source="pkt_counter_s"; record=mean);

        @signal[disk_backlog_s];
        @statistic[disk_backlog](source="disk_backlog_s"; record=vector);

        @signal[service_time_s];
        @statistic[service_time_disk](source="service_time_s"; record=mean);

    gates:
        input from_processor;
        output to_processor;
}
