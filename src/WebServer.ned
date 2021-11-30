
package nclients_server_sim;

simple WebServer
{
    parameters:
        //Service rate of the Web Server
        double serv_rate_w @unit(Hz)=default(1Hz);
        
    gates:
        input web_in;
        output web_out;
}
