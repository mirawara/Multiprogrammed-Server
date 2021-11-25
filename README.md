# NClients-Server-Sim

A multiprogrammed server provides service to n concurrent clients, whose transactions may involve
processing, access to disk, and remote queries to a distant web server. More specifically:
1) A new transaction always requires some processing time as a first step;
2) After the processing has occurred:
    - with a probability p1 the transaction is terminated and the reply is sent to the client that
    originated it;
    - with a probability p2 a disk access is required, and then a new processing is required;
    - with a probability 1-p1-p2 a remote query is required, and then a new processing is
    required.
3) A user that receives a reply immediately issues another request.
The processor, the disk and the remote web server handle one request at a time in a FIFO order.
Processing, disk access and remote query service demands are exponential IID RVs, and they are
different from one iteration to another, even for the same transaction.

Authors:
Gaetano Sferrazza, Edoardo Loni, Lorenzo Mirabella.

University of Pisa
