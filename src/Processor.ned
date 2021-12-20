package multiprogrammed_server;
simple Processor
{
    parameters:
        //Processor's service rate
        double service_rate =default(1);
        
        int Nq_window @unit(s)= default(1s);
        int timeWindow @unit(s)=default(10s);

        //Signal for the throughput
        @signal[pkt_counter_s];
        @statistic[pkt_counter](source="pkt_counter_s"; record=mean);
        
        @signal[processor_backlog_s];
        @statistic[processor_backlog](source="processor_backlog_s"; record=mean,vector);
        
        @signal[service_time_s];
        @statistic[service_time](source="service_time_s"; record=mean);

    gates:
        input from_clients;
        input from_disk;
        input from_web_server;
        output to_clients;
        output to_disk;
        output to_web_server;
}