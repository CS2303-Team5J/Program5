// Author Erik Nadel (einadel@wpi.edu) | Jacob Watson (jrwatson@wpi.edu)
#include <iostream>
#include "host.h"
#include "router.h"
#include "receiver.h"
#include "packet.h"
#include "eventlist.h"
#include "grid.h"
#include "stack.h"
#include <vector>

using namespace std;
using namespace EIN_JRW_Prog5;



int main()
{
    int currentSimTime = 0;
    EventList global;
    Host S1(&global,0);
    Host S2(&global,5);

    Grid routerGrid(20,20);
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

    int numPackets = 400;
    // Create the routers / receiver
    Router *M1 = new Router(&global,"M1",1,&routerGrid);
    Router *M2 = new Router(&global,"M2",2,&routerGrid);
    Receiver *R1 = new Receiver(&global,4);

//while(R1->getNumPacketsReceived() != numPackets) // Run the cycle until the host gets all the packets
//{
//
//    S1.cycle(currentSimTime,M1,1,2);
//    if(currentSimTime >= 3)
//        S2.cycle(currentSimTime,M1,1,2);
//
//    M1->cycle(currentSimTime,M2,2,3);
//
//    M2->cycle(currentSimTime,M3,2,5);
//
//    M3->cycle(currentSimTime,R1,2,5);
//
//    currentSimTime++;
//}

    Stack<SimNode*> teststack;
    teststack.push(&S1);
    teststack.push(M1);
    teststack.push(M2);
    teststack.push(R1);

    cout << teststack.previewPop()->getID() << endl;
    teststack.pop();
    cout << teststack.previewPop()->getID() << endl;
    teststack.pop();
    cout << teststack.previewPop()->getID() << endl;


    //global.printEventList();

    // Print the stats

    //cout << "Total Sim time: "  << currentSimTime / 1000.0  << " seconds " << endl;
    //cout << "Max queue of " << M1->getName() << " " << M1->getMaxQueue() << " packets" << std::endl;
    //cout << "Max queue of " << M2->getName() << " " << M2->getMaxQueue() << " packets" << std::endl;
    //cout << "Max queue of " << M3->getName() << " " << M3->getMaxQueue() << " packets" << std::endl;
    //int numPacketsToSend = S1.getNumPackets() + S2.getNumPackets();
    //int packetsReceived = 0;
    // Print the average response time

    cout << "Average packet response time " << R1->getAverageResponseTime() / 1000.0 << " seconds" << endl;
    return 0;
}


