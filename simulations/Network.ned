//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package nclients_server_sim.simulations;

import nclients_server_sim.Clients;
import nclients_server_sim.Server;
import nclients_server_sim.WebServer;


network Network
{
    submodules:
        clients: Clients {
            @display("p=64,49");
        }
        server: Server {
            @display("p=148,49");
        }
        webServer: WebServer {
            @display("p=227,49");
        }
    connections:
        clients.client_out --> server.from_clients;
        server.to_clients --> clients.client_in;
        server.to_web_server --> webServer.web_in;
        webServer.web_out --> server.from_web_server;
}
