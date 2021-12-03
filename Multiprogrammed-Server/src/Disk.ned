 
package multiprogrammed_server;

simple Disk
{
    //Service rate of the disk
    parameters:
        double service_rate @unit(Hz);
        
    gates:
        input from_processor;
        output to_processor;
}
