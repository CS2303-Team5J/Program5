// Author Jacob Watson (jrwatson@wpi.edu)  | Erik Nadel (einadel@wpi.edu)
#include "packet.h"
#include "host.h"
#include <iostream>

namespace EIN_JRW_Prog5
{

    Host::Host(EventList* e, int id, Grid* g)
    {
        events = e;
        nodeID = id;
        simGrid = g;
        simGrid->addObject(this);
        packetBeingSent = NULL;
        packetsSent = 0;
    }

    Packet Host::getPacket()
    {
        if(packets.size() != 0) // Is there a packet to get?
        {
            Packet p = packets[0]; // Get the first packet and remove from the packet list
            packets.erase(packets.begin());
            return p;
        }
        else
        {
            // No packet was found. Return a bad packet
            Packet *noPacket = new Packet(-1,"something bad happened...",ARRIVED);
            return *noPacket;
        }
    }
    void Host::sendPacket(int simTime)
    {
        Packet p  = this->getPacket(); // Get the next packet to send
        p.setArrival(simTime);
        //p.printPath();
        events->addNewEvent(p); // Add to the event list that the packet arrived
        //std::cout << "arrived at " << simTime << std::endl;
        //std::cout << " - - -" << std::endl;

        //events->printEventList();

        // Remove the arrival event


        // Remove this host from the route
        p.route().pop();

        SimNode *nextDest  = p.route().previewPop();
        sendTimeRem = p.getSize() + p.calculatePropTime(this->getLocation(),nextDest->getLocation());
        p.setState(TRANSMITTED,simTime+p.getSize());
        events->addModifiedEvent(p);
        p.setState(PROPAGATED,simTime+sendTimeRem);
        events->addModifiedEvent(p);
        //sendTimeRem = 5;
        sendTime = sendTimeRem;
        packetBeingSent = new Packet(); // reset the packetBeing Sent
        hasTransmitted = false;
        *packetBeingSent = p; // Set the packet being sent
        packetsSent++;
        std::cout << nodeID << " Sent " << packetsSent << std::endl;

    }

    void Host::cycle(int simTime)
    {
        if(packetBeingSent == NULL)
        {
            // Do we have another packet to send?
            if(packets.size() != 0)
            {
                sendPacket(simTime); // Send it
            }
        }

        while(events->hasRelevantEvent(simTime,ARRIVED,this))
            events->getNextRelevantEvent(simTime,ARRIVED,this);

        if(packetBeingSent != NULL) // Are we processing a packet?
        {

            sendTimeRem--;



            if(sendTimeRem < sendTime - packetBeingSent->getSize() && !hasTransmitted) // Has the packet finished transmitting?
            {
                //packetBeingSent->setState(TRANSMITTED,simTime); // Set the state to transmitted
                //events->addModifiedEvent(*packetBeingSent); // Add that event to the event list
                //std::cout << " -- - -" << std::endl;
                //events->printEventList();
                hasTransmitted = true; // Set that the packet has finished transmitting
                // No longer busy sending
                events->getNextRelevantEvent(simTime,TRANSMITTED,packetBeingSent->route().previewPop());
                Packet *temp = packetBeingSent;
                packetBeingSent = NULL;
                delete temp;
            }

//            if(sendTimeRem <= 0) // Is the packet done sending?
//            {
//                //packetBeingSent->printPath();
//                SimNode *nextDest = packetBeingSent->route().previewPop();
//                nextDest->receivePacket(*packetBeingSent,simTime); // Put the packet at the router.
//                Packet *temp = packetBeingSent; // Delete the packet being sent from the router cache
//                packetBeingSent = NULL;
//                delete temp;
//            }


        }

    }

    location Host::getLocation()
    {
        return location(this->nodeLoc.GetxCoord(),-1);
    }
}
