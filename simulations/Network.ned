
package multiprogrammed_server.simulations;

import multiprogrammed_server.Clients;
import multiprogrammed_server.Server;
import multiprogrammed_server.WebServer;

//Multiprogrammed Server Network
network Network
{
    submodules:
        
        //N Clients (represented by one simple module)
        clients: Clients {
            @display("p=64,49");
        }
        
        //Server
        server: Server {
            @display("p=148,49");
        }
        
        //Web Server
        webServer: WebServer {
            @display("p=227,49");
        }
        
    connections:
        //Connection between the Client's output gate
        //and the Server's input gate
        clients.client_out --> server.from_clients;
        
        //Connection between the Server's output gate
        //and the Client's input gate
        server.to_clients --> clients.client_in;
        
        //Connection between the Server's output gate
        //and the Web Server's input gate
        server.to_web_server --> webServer.web_in;
        
        //Connection between the Web Server's output gate
        //and the Server's input gate
        webServer.web_out --> server.from_web_server;
}
