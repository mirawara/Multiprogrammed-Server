package multiprogrammed_server;

simple Clients
{
    parameters:
        //Number of clients
        int num_clients=default(1);

        //Signal for the throughput
        @signal[throughput_s](type="long");
        @statistic[throughput](source="throughput_s"; record=last);
        
        //@signal[service_rate](type="long");
        //@statistic[throughput1](source="service_rate"; record=mean, vector);

    gates:
        input client_in;
        output client_out;
}
