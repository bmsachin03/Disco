#include <string.h>
#include <omnetpp.h>

using namespace omnetpp;

class Txc1 : public cSimpleModule
{
    cMessage *timeoutEvent; // delay for packets
    int stop; // shows timeout

 protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
};

// The module class needs to be registered with OMNeT++
Define_Module(Txc1);

void Txc1::initialize()
{
    stop = 1;
    timeoutEvent = new cMessage("timeoutEvent");
    scheduleAt(simTime() + 20, timeoutEvent); // stop after 20 seconds
        if (strcmp("tic", getName()) == 0)
        {
        // create and send first message on gate "out". "tictocMsg" is an
        // arbitrary string which will be the name of the message object.
        //cMessage *msg = new cMessage("tictocMsg");
        cPacket *msg = new cPacket("msg 512");
        msg->setByteLength (524800); // setting packet size for 512 kbytes
        send(msg, "out");
    }
}

void Txc1::handleMessage(cMessage *msg)
{
    // The handleMessage() method is called whenever a message arrives
    // at the module. Here, we just send it to the other module, through
    // gate `out'. Because both `tic' and `toc' does the same, the message
    // will bounce between the two.
    //send(msg, "out"); // send out the message
    // If timer expires stop sending message
    if (msg == timeoutEvent)
    {
            stop = 0;
    }
    // If timer not expires send message
    if (stop == 1)
    {
        if (strcmp("tic", getName()) == 0)
        {

                sendDelayed(msg, 1, "out") ;
        }
        else
        {
            sendDelayed(msg, exponential(1),"out");
            /* toc has a delay of X seconds, where X is exponentially distributed with parameter 1*/
        }
    }
}

