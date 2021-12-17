package multiprogrammed_server;
simple Processor
{
    parameters:
        //Processor's service rate
        double service_rate =default(1);
        
        @signal[processor_backlog_s];
        @statistic[processor_backlog](source="processor_backlog_s"; record=mean,vector);

    gates:
        input from_clients;
        input from_disk;
        input from_web_server;
        output to_clients;
        output to_disk;
        output to_web_server;
}
