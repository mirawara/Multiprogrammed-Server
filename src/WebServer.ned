package multiprogrammed_server;

simple WebServer
{
    parameters:

        //Service rate of the Web Server
        double serv_rate_w =default(1);
        
        @signal[wserver_backlog_s];
        @statistic[wserver_backlog](source="wserver_backlog_s"; record=vector);
        
    gates:
        input web_in;
        output web_out;
}
