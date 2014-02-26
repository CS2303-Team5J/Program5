// Author Erik Nadel (einadel@wpi.edu) | Jacob Watson (jrwatson@wpi.edu)
#include <iostream>
#include "host.h"
#include "router.h"
#include "receiver.h"
#include "packet.h"
#include "eventlist.h"
using namespace std;
using namespace EIN_JRW_Lab5;

int main()
{
    int currentSimTime = 0;
    EventList global;
    Host S1(&global);
    Host S2(&global);
    for(int x = 0; x < 100; ++x) // Fill host 1 with 100 packets of size (0-99) 
    {
        Packet p(x,"S1",ARRIVED);
        S1.addPacket(p);
    }
    for(int x = 100; x < 200; ++x) // Fill host 2 with 100 packets of size 100-199
    {
        Packet p(x,"S2",ARRIVED);
        S2.addPacket(p);
    }

    int numPackets = 200;
    // Create the routers / receiver
    Router *M1 = new Router(&global,"M1");
    Router *M2 = new Router(&global,"M2");
    Receiver *R1 = new Receiver();

while(R1->getNumPacketsReceived() != numPackets) // Run the cycle until the host gets all the packets
{

    S1.cycle(currentSimTime,M1,1,2);
    if(currentSimTime >= 3)
        S2.cycle(currentSimTime,M1,1,2);

    M1->cycle(currentSimTime,M2,2,3);

    M2->cycle(currentSimTime,R1,2,5);

    currentSimTime++;
}



    //global.printEventList();

    // Print the stats

    cout << "Total Sim time: "  << currentSimTime / 1000.0  << " seconds " << endl;
    cout << "Max queue of " << M1->getName() << " " << M1->getMaxQueue() << " packets" << std::endl;
    cout << "Max queue of " << M2->getName() << " " << M2->getMaxQueue() << " packets" << std::endl;
    //int numPacketsToSend = S1.getNumPackets() + S2.getNumPackets();
    //int packetsReceived = 0;
    // Print the average response time

    cout << "Average packet response time " << R1->getAverageResponseTime() / 1000.0 << " seconds" << endl;
    return 0;
}
