package multiprogrammed_server;

module Server
{
    parameters:
        //Probability that the transaction is terminated 
        //and the reply is sent to the client that originated it
        double p1;

        //Probability that a disk access is required
        double p2;

    gates:
        input from_clients;
        input from_web_server;
        output to_clients;
        output to_web_server;

    submodules:
        //The server is composed by a processor and a disk
        processor: Processor;
        disk: Disk;

    connections:
        //Connection between the Server's input gate (connected with the Client's output)
        //and the Processor's input gate
        from_clients --> processor.from_clients;

        //Connection between the Server's input gate (connected with the Web Server's output)
        //and the Processor's input gate
        from_web_server --> processor.from_web_server;

        //Connection between the Processor's output gate 
        //and the Server's output gate (connected with the Client's input)
        processor.to_clients --> to_clients;

        //Connection between the Processor's output gate 
        //and the Server's output gate (connected with the Web Server's input)
        processor.to_web_server --> to_web_server;

        //Connection between the Processor's output gate 
        //and the Disk's input gate
        processor.to_disk --> disk.from_processor;

        //Connection between the Disk's output gate 
        //and the Processor's input gate
        disk.to_processor --> processor.from_disk;
}