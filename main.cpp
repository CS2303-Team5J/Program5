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
#include <cstdlib>

using namespace std;
using namespace EIN_JRW_Prog5;


Stack<SimNode*> createRoutePath(std::string inputpath,std::vector<SimNode*> networkNodes);
void printSimMap(Grid hosts, Grid routers, Grid receivers);

int main()
{
    int currentSimTime = 0;
    EventList global;


    Grid routerGrid(20,20);
    Grid receiverGrid(20,1);
    Grid hostGrid(20,1);



    int numPackets = 100;
    // Create the routers / receiver
    Host S1(&global,1,&hostGrid);
    Router *M1 = new Router(&global,"M1",2,&routerGrid);
    Router *M2 = new Router(&global,"M2",3,&routerGrid);
    Receiver *R1 = new Receiver(&global,4,&receiverGrid,routerGrid.getYLength());




    int b = 5;


    vector<SimNode*> network;
    network.push_back(&S1);
    network.push_back(M1);
    network.push_back(M2);
    network.push_back(R1);

    for(int y = 0; y < network.size(); ++y)
    {
        cout << network[y]->getID() << ": " <<network[y] << endl;
    }
    cout << "THESE ARE THE CORRECT POINTERS!!!" << endl;

    for(int x = 0; x < 100; ++x) // Fill host 1 with 100 packets of size (0-99)
    {
        Packet p(2,"S1",ARRIVED);
        p.setPath(createRoutePath("1 2 3 4",network));
        S1.addPacket(p);
    }

    printSimMap(hostGrid,routerGrid,receiverGrid);

     do// Run the cycle until the host gets all the packets
    {

    S1.cycle(currentSimTime);

    M1->cycle(currentSimTime);

    M2->cycle(currentSimTime);

    //global.printEventList();

    R1->cycle(currentSimTime);

    currentSimTime++;
    }while(!global.isEmpty());


    global.printEventList();

    // Print the stats

    cout << "Total Sim time: "  << currentSimTime / 1000.0  << " seconds " << endl;
    cout << "Max queue of " << M1->getName() << " " << M1->getMaxQueue() << " packets" << std::endl;
    cout << "Max queue of " << M2->getName() << " " << M2->getMaxQueue() << " packets" << std::endl;
    //cout << "Max queue of " << M3->getName() << " " << M3->getMaxQueue() << " packets" << std::endl;
    //int numPacketsToSend = S1.getNumPackets() + S2.getNumPackets();
    //int packetsReceived = 0;
    // Print the average response time

    cout << "Average packet response time " << R1->getAverageResponseTime() / 1000.0 << " seconds" << endl;
    return 0;
}



Stack<SimNode*> createRoutePath(std::string inputpath,std::vector<SimNode*> networkNodes)
{
        std::string delim = " ";
        int start = 0;
        int end;
        std::vector<std::string> splitString;
        Stack<SimNode*> route;
        // Until find returns nothing (string::npos)
        while((end = inputpath.find(delim,start)) != std::string::npos)
        {
            // Get the substring up to the delimter
            // end is the position of the delimiting string
            splitString.push_back(inputpath.substr(start,end-start));
            start = end + delim.size();
        }
        // Get the last remaining word
        splitString.push_back(inputpath.substr(start));

        for(int i = 0; i < networkNodes.size(); i++)
        {
            for(int x = 0; x < splitString.size(); ++x)
            {
                //cout << networkNodes[x]->getID() << ": " << networkNodes[x] << endl;
                if(networkNodes[i]->getID() == atoi(splitString[x].c_str()))
                    route.push(networkNodes[i]);
            }
        }

        return route;
}

void printSimMap(Grid hosts, Grid routers, Grid receivers)
{
    hosts.print();
    routers.print();
    receivers.print();
}
