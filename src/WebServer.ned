package multiprogrammed_server;

simple WebServer
{
    parameters:

        //Service rate of the Web Server
        double serv_rate_w = default(1);

		//Timer period for the observation of the number of queued requests
        int Nq_window @unit(s) = default(1s);
        //Time window in which the number of completed requests is counted
        int timeWindow @unit(s) = default(10s);

        //Signal for the throughput
        @signal[pkt_counter_s];
        @statistic[pkt_counter_ws](source="pkt_counter_s"; record=mean);

		//Signal for the number of queued reqyests
        @signal[wserver_queued_req_s];
        @statistic[wserver_queued_req](source="wserver_queued_req_s"; record=vector);

        @signal[service_time_s];
        @statistic[service_time_ws](source="service_time_s"; record=mean);

    gates:
        input web_in;
        output web_out;
}
