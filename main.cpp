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
#include <ctime>

using namespace std;
using namespace EIN_JRW_Prog5;

// Utility function prototypes
// Author Erik Nadel (einadel@wpi.edu)
// Generate a route path based on the given node ids and network of nodes
Queue<SimNode*> createRoutePath(std::vector<int> desiredPath,std::vector<SimNode*> networkNodes);
// Author Erik Nadel (einadel@wpi.edu)
// print the sim map
void printSimMap(Grid hosts, Grid routers, Grid receivers);
// Author Erik Nadel (einadel@wpi.edu)
// Get the pointer to a node based on its id
SimNode* getNodeByID(int id,vector<SimNode*> networkNodes);


int main(int argc, char* argv[])
{
    // Check for valid arguments
    if(argc != 5)
    {
        cout << "INVALID ARGUMENTS! " << endl;
        cout << "should be ./prog5 <numsources> <numreceivers> <numMules> <dimension>" << endl;
        return 0;
    }

    // Seed the randomness
    srand(time(NULL));

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

    // Create all of the mules
    for(int x = numSources+1; x <= numSources+numMules; ++x )
    {
        Router *M = new Router(&global,"M",x,&routerGrid);
        network.push_back(M);
    }

    // Create all of the receivers
    for(int x = numSources+numMules+1; x <= numSources+numReceivers+numMules; ++x)
    {
        Receiver *R = new Receiver(&global,x,&receiverGrid,routerGrid.getYLength());
        network.push_back(R);
    }



    // Variables for input
    int sourceID;
    int arrivalTime;
    int packets;
    int pkt_size;
    int SR_size;
    int routenode;
    vector<int> *SR;


    // Process Input
    for(int x = 0; x < numSources; ++x)
    {
        SR = new vector<int>();
        cin >> sourceID >> arrivalTime >> packets >> pkt_size >> SR_size;
        for(int y = 0; y < SR_size; ++y)
        {
            cin >> routenode;
            SR->push_back(routenode);
        }

        // Set the arrival time of the host
        getNodeByID(sourceID,network)->setArrivalTime(arrivalTime);

        // Put the correct number of packets into the host ready to send
        for(int z = 0; z < packets; z++)
        {
            Packet p(pkt_size,sourceID,ARRIVED);
            p.setPath(createRoutePath(*SR,network));
            getNodeByID(sourceID,network)->addPacket(p);
            getNodeByID(sourceID,network)->setArrivalTime(arrivalTime);
        }

        delete SR;



    }

    // Print initial Grid
    printSimMap(hostGrid,routerGrid,receiverGrid);

    // Invoke the cycle of everything until the event list is done
     do
    {
        for(size_t x = 0; x < network.size(); ++x)
        {
            if(network[x]->getArrivalTime() <= currentSimTime)
                network[x]->cycle(currentSimTime);
        }

        if(currentSimTime != 0 && currentSimTime % 10 == 0)
        {
            printSimMap(hostGrid,routerGrid,receiverGrid);
            cout  << endl;
        }

        currentSimTime++;


    }while(!global.isEmpty());

    // Confirming that its empty based on nothing printing
    global.printEventList();

    // Print the stats

    cout << "Total Sim time: "  << currentSimTime / 1000.0  << " seconds " << endl;
    cout << "=================================" << endl;
    cout << "Max Queue sizes for mules " << endl;
    cout << "---------------------------------" << endl;

    // Get the max queue sizes for all the mules
    for(size_t x = 0; x <network.size(); x++)
    {
        SimNode *s = getNodeByID(x,network);
        if(s != NULL)
        {
            if(s->getMaxQueue() >= 0) // Is it a valid max queue number?
            {
                // It must be a mule. print its max queue
                cout << "Mule: " << s->getID() << "-->"  << s->getMaxQueue() << " packets" << endl;
            }
        }
    }

    // Print the receiver stats
    int numPackets  = 0;
    int totalResponseTime = 0;
    double totalAverageVariance = 0;
    cout << endl;
    cout << "Receiver Stats " << endl;
    cout << "--------------" << endl;
    for(size_t x = 0; x <network.size(); x++)
    {
        SimNode *s = getNodeByID(x,network);
        if(s != NULL)
        {
            if(s->getAverageResponseTime() > 0.0)
            {
                 s->processPacketStats();
                 numPackets += s->getNumPacketsReceived();
                 totalResponseTime += s->getTotalResponseTime();
                 totalAverageVariance += s->getAverageVariance();
            }
        }
    }

    cout << endl;

    // Total mean
    cout << "The average response time for all " << numPackets << " packets was " << ((double) totalResponseTime / (double) numPackets) / 1000.0 << " seconds "<< endl;
    cout << "The average variance of the delay of the packets at the receivers was " << (totalAverageVariance / (double) numReceivers) / 1000.0 << " seconds " << endl;
    return 0;
}



Queue<SimNode*> createRoutePath(std::vector<int> desiredPath,std::vector<SimNode*> networkNodes)
{
        Queue<SimNode*> route;

        for(size_t i = 0; i < desiredPath.size(); i++)
        {
            for(size_t x = 0; x < networkNodes.size(); ++x)
            {
                //cout << networkNodes[x]->getID() << ": " << networkNodes[x] << endl;
                if(networkNodes[x]->getID() == desiredPath[i])
                {
                    //cout << networkNodes[x]->getID() << endl;
                    route.push(networkNodes[x]);
                }
            }
        }

        return route;
}

void printSimMap(Grid hosts, Grid routers, Grid receivers)
{
    routers.printBetween(hosts,routers,receivers);
}

SimNode* getNodeByID(int id, std::vector<SimNode*> networkNodes)
{
    for(size_t i = 0; i < networkNodes.size(); ++i)
    {
        if(networkNodes[i]->getID() == id)
            return networkNodes[i];
    }
    return NULL;
}
