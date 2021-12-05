 package multiprogrammed_server;

simple Disk
{
    parameters:
        //Service rate of the disk
        double service_rate @unit(Hz);
        
    gates:
        input from_processor;
        output to_processor;
}
