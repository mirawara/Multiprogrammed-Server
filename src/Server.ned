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

package nclients_server_sim;

module Server
{
    parameters:
        double p1;
        double p2;
    gates:
        input from_clients;
        input from_web_server;
        output to_clients;
        output to_web_server;
    submodules:
        processor: Processor;
        disk: Disk;
    connections:
        from_clients --> processor.from_clients;
        from_web_server --> processor.from_web_server;
        processor.to_clients --> to_clients;
        processor.to_web_server --> to_web_server;
        processor.to_disk --> disk.from_processor;
        disk.to_processor --> processor.from_disk;
}
