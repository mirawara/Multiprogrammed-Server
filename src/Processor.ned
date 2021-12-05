package multiprogrammed_server;
simple Processor
{
    parameters:
        //Processor's service rate
        double service_rate =default(1);

    gates:
        input from_clients;
        input from_disk;
        input from_web_server;
        output to_clients;
        output to_disk;
        output to_web_server;
}
