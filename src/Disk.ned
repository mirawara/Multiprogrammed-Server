 package multiprogrammed_server;

simple Disk
{
    parameters:
        //Service rate of the disk
        double service_rate = default(1);
        
        @signal[disk_backlog_s];
        @statistic[disk_backlog](source="disk_backlog_s"; record=vector);
        
    gates:
        input from_processor;
        output to_processor;
}