package multiprogrammed_server;

simple WebServer
{
    parameters:

        //Service rate of the Web Server
        double serv_rate_w = default(1);

        int Nq_window @unit(s) = default(1s);
        int timeWindow @unit(s) = default(10s);

        //Signal for the throughput
        @signal[pkt_counter_s];
        @statistic[pkt_counter_ws](source="pkt_counter_s"; record=mean);

        @signal[wserver_backlog_s];
        @statistic[wserver_backlog](source="wserver_backlog_s"; record=vector);

        @signal[service_time_s];
        @statistic[service_time_ws](source="service_time_s"; record=mean);

    gates:
        input web_in;
        output web_out;
}
