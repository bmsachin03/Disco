//sachinkumar


simple Txc1
{
    gates:
        input in;
        output out;
}

//
// Two instances (tic and toc) of Txc1 connected both ways.
// Tic and toc will pass messages to one another.
//
network Tictoc1
{
    submodules:
        tic: Txc1;
        toc: Txc1;
    connections:
        tic.out --> {  datarate=8Mbps; } --> toc.in;// Setting the channel rate to 1 MBps
        tic.in <-- {  datarate=8Mbps; } <-- toc.out;
}

