#include "packet.h"
#include "host.h"
#include <iostream>

namespace EIN_JRW_Prog5
{

    //Author Erik Nadel (einadel@wpi.edu)
    Host::Host(EventList* e, int id, Grid* g)
    {
        events = e;
        nodeID = id;
        simGrid = g;
        simGrid->addObject(this);
        packetBeingSent = NULL;
        packetsSent = 0;
    }

    // Author Jacob Watson (jrwatson@wpi.edu)
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
            Packet *noPacket = new Packet(-1,-1,ARRIVED);
            return *noPacket;
        }
    }

    //Author Erik Nadel (einadel@wpi.edu)
    void Host::sendPacket(int simTime)
    {
        Packet p  = this->getPacket(); // Get the next packet to send
        p.setArrival(simTime);

        events->addNewEvent(p); // Simulate the arrival of the packet at this time

        // Add to the event list that the packet arrived
        std::cout << "[" << simTime << "] "<< " packet arrived at host " << this->getID() << std::endl;



        // Remove this host from the route
        p.route().pop();

        SimNode *nextDest  = p.route().previewPop();
        packetsSent++;
        sendTimeRem = p.getSize() + p.calculatePropTime(this->getLocation(),nextDest->getLocation());
        std::cout << "[" << simTime << "] "<< " started sending packet " << packetsSent << " from host" << this->getID() << std::endl;

        // Add the future events to the event list
        p.setState(TRANSMITTED,simTime+p.getSize());
        events->addModifiedEvent(p);
        p.setState(PROPAGATED,simTime+sendTimeRem);
        events->addModifiedEvent(p);

        // Make the host busy during transmittion time
        sendTime = sendTimeRem;
        packetBeingSent = new Packet(); // reset the packetBeing Sent
        hasTransmitted = false;
        *packetBeingSent = p; // Set the packet being sent




    }

    //Author Erik Nadel (einadel@wpi.edu)
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

        // Get rid of a arrived events
        while(events->hasRelevantEvent(simTime,ARRIVED,this))
            events->getNextRelevantEvent(simTime,ARRIVED,this);

        if(packetBeingSent != NULL) // Are we processing a packet?
        {

            sendTimeRem--;

            if(sendTimeRem < sendTime - packetBeingSent->getSize() && !hasTransmitted) // Has the packet finished transmitting?
            {
                hasTransmitted = true; // Set that the packet has finished transmitting
                // No longer busy sending
                events->getNextRelevantEvent(simTime,TRANSMITTED,packetBeingSent->route().previewPop());
                std::cout << "[" << simTime << "] "<< " packet transmitted from host " << this->getID() << std::endl;
                Packet *temp = packetBeingSent;
                packetBeingSent = NULL;
                delete temp;
            }

        }

    }

    // Author Jacob Watson (jrwatson@wpi.edu)
    location Host::getLocation()
    {
        return location(this->nodeLoc.GetxCoord(),-1);
    }
}
