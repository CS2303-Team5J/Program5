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
#include <string>

using namespace std;
using namespace EIN_JRW_Prog5;


Stack<SimNode*> createRoutePath(std::vector<int> desiredPath,std::vector<SimNode*> networkNodes);
void printSimMap(Grid hosts, Grid routers, Grid receivers);
SimNode* getNodeByID(int id,vector<SimNode*> networkNodes);

int main(int argc, char* argv[])
{
    if(argc != 5)
    {
        cout << "INVALID ARGUMENTS! " << endl;
        cout << "should be ./prog4 <numsources> <numreceivers> <numMules> <dimension>" << endl;
        return 0;
    }

    // command line arguments
    int numSources = atoi(argv[1]);
    int numReceivers = atoi(argv[2]);
    int numMules = atoi(argv[3]);
    int dimension = atoi(argv[4]);

    cout << "Num sources " << numSources << endl;
    cout << "Num receivers " << numReceivers << endl;
    cout << "numMules " << numMules << endl;
    cout << "Dimension " << dimension << endl;


    // Global variables
    int currentSimTime = 0;
    EventList global;
    vector<SimNode*> network;



    //// Initialization

    Grid routerGrid(dimension,dimension);
    Grid receiverGrid(dimension,1);
    Grid hostGrid(dimension,1);

    // Create all the hosts
    for(int x = 1; x <= numSources; ++x)
    {
        Host *S = new Host(&global,x,&hostGrid);
        network.push_back(S);
    }
//    for(int x = 0; x < network.size(); ++x)
//    {
//        cout << "ID " << network[x]->getID() << endl;
//    }

    // Create all of the mules
    for(int x = numSources+1; x <= numSources+numMules; ++x )
    {
        Router *M = new Router(&global,"M",x,&routerGrid);
        cout << "Creating router " << x << endl;
        network.push_back(M);
    }

    // Create all of the receivers
    for(int x = numSources+numMules+1; x <= numSources+numReceivers+numMules; ++x)
    {
        Receiver *R = new Receiver(&global,x,&receiverGrid,routerGrid.getYLength());
        network.push_back(R);
    }



    int sourceID;
    int arrivalTime;
    int packets;
    int pkt_size;
    int SR_size;
    int routenode;
    vector<int> SR;



    cout << "test " << getNodeByID(3,network)->getID() << endl;

    for(int x = 0; x < 1; ++x)
    {
        cin >> sourceID >> arrivalTime >> packets >> pkt_size >> SR_size;
        for(int y = 0; y < SR_size; ++y)
        {
            cin >> routenode;
            SR.push_back(routenode);
        }

        getNodeByID(sourceID,network)->setArrivalTime(arrivalTime);

        for(int z = 0; z < packets; z++)
        {
            Packet p(pkt_size,"S" + sourceID,ARRIVED);
            p.setPath(createRoutePath(SR,network));
            getNodeByID(sourceID,network)->addPacket(p);
        }
    }

    getNodeByID(25,network)->identifyType();

//    Host S1(&global,1,&hostGrid);
//    Host S2(&global,2,&hostGrid);
//    Router *M1 = new Router(&global,"M1",3,&routerGrid);
//    Router *M2 = new Router(&global,"M2",4,&routerGrid);
//    Receiver *R1 = new Receiver(&global,5,&receiverGrid,routerGrid.getYLength());




//    for(int x = 0; x < 100; ++x) // Fill host 1 with 100 packets of size (0-99)
//    {
//        Packet p(2,"S1",ARRIVED);
//        p.setPath(createRoutePath("1 3 4 5",network));
//        S1.addPacket(p);
//    }

    printSimMap(hostGrid,routerGrid,receiverGrid);

     do
    {
        for(int x = 0; x < network.size(); ++x)
        {
            network[x]->cycle(currentSimTime);
        }
        //cout << "SIMTIME" << currentSimTime << endl;
//        S1.cycle(currentSimTime);
//        S2.cycle(currentSimTime);
//
//        M1->cycle(currentSimTime);
//
//        M2->cycle(currentSimTime);
//
//
//
//        R1->cycle(currentSimTime);

        //global.printEventList();

        //cout << S1.getPacketsSent() << " " << S2.getPacketsSent() << endl;

        currentSimTime++;
    }while(!global.isEmpty());


    global.printEventList();

    // Print the stats

    cout << "Total Sim time: "  << currentSimTime / 1000.0  << " seconds " << endl;
    for(int x = 0; x <network.size(); x++)
    {
        SimNode *s = getNodeByID(x,network);
        if(s != NULL)
        {
        if(s->getMaxQueue() != -1)
        {
            cout << s->getID() << " "  << s->getMaxQueue() << endl;
        }
        }
    }
//    cout << "Max queue of " << M1->getName() << " " << M1->getMaxQueue() << " packets" << std::endl;
//    cout << "Max queue of " << M2->getName() << " " << M2->getMaxQueue() << " packets" << std::endl;
    //cout << "Max queue of " << M3->getName() << " " << M3->getMaxQueue() << " packets" << std::endl;
    //int numPacketsToSend = S1.getNumPackets() + S2.getNumPackets();
    //int packetsReceived = 0;
    // Print the average response time

    cout << "Average packet response time " << getNodeByID(52,network)->getAverageResponseTime() / 1000.0 << " seconds" << endl;
    return 0;
}



Stack<SimNode*> createRoutePath(std::vector<int> desiredPath,std::vector<SimNode*> networkNodes)
{
//        std::string delim = " ";
//        int start = 0;
//        int end;
//        std::vector<std::string> splitString;
        Stack<SimNode*> route;
//        // Until find returns nothing (string::npos)
//        while((end = inputpath.find(delim,start)) != std::string::npos)
//        {
//            // Get the substring up to the delimter
//            // end is the position of the delimiting string
//            splitString.push_back(inputpath.substr(start,end-start));
//            start = end + delim.size();
//        }
//        // Get the last remaining word
//        splitString.push_back(inputpath.substr(start));

        for(int i = 0; i < networkNodes.size(); i++)
        {
            for(int x = 0; x < desiredPath.size(); ++x)
            {
                //cout << networkNodes[x]->getID() << ": " << networkNodes[x] << endl;
                if(networkNodes[i]->getID() == desiredPath[x])
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

SimNode* getNodeByID(int id, std::vector<SimNode*> networkNodes)
{
    for(int i = 0; i < networkNodes.size(); ++i)
    {
        if(networkNodes[i]->getID() == id)
            return networkNodes[i];
    }
    return NULL;
}
