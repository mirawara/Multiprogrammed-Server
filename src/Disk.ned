 package multiprogrammed_server;

simple Disk
{
    parameters:
        //Service rate of the disk
        double service_rate = default(1);
        
        int Nq_window @unit(s)= default(1s);
        
        @signal[disk_backlog_s];
        @statistic[disk_backlog](source="disk_backlog_s"; record=vector);
        
    gates:
        input from_processor;
        output to_processor;
}