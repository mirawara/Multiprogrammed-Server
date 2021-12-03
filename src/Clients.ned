
package multiprogrammed_server;

simple Clients
{
    parameters:
        //Number of clients
        int num_clients=default(1);
        @signal[throughput_s];
        @statistic[throughput](source="throughput_s"; record=vector);
        

        //signal and recorder for the service rate in order
        //to compute the throghput
        @signal[service_rate];
        @statistic[throughput1](source="service_rate"; record=mean, vector);

    gates:
        input client_in;
        output client_out;
}
