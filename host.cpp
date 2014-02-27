// Author Jacob Watson (jrwatson@wpi.edu)  | Erik Nadel (einadel@wpi.edu)
#include "packet.h"
#include "host.h"
namespace EIN_JRW_Prog5
{
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
            Packet *noPacket = new Packet(-1,"NOTFOUND",ARRIVED);
            return *noPacket;
        }
    }
    void Host::sendPacket(int trans,int prop, int simTime)
    {
        Packet p  = this->getPacket(); // Get the next packet to send
        p.setArrival(simTime);
        events->addNewEvent(p); // Add to the event list that the packet arrived

        sendTimeRem = trans + prop;
        sendTime = trans + prop;
        packetBeingSent = new Packet(); // reset the packetBeing Sent
        hasTransmitted = false;
        *packetBeingSent = p; // Set the packet being sent
    }

    void Host::cycle(int simTime, Router* r,int trans, int prop)
    {
        if(packetBeingSent == NULL)
        {
            // Do we have another packet to send?
            if(packets.size() != 0)
            {
                sendPacket(trans,prop, simTime); // Send it
            }
        }
        if(packetBeingSent != NULL) // Are we processing a packet?
        {

            sendTimeRem--;

            if(sendTimeRem < sendTime - trans && !hasTransmitted) // Has the packet finished transmitting?
            {
                packetBeingSent->setState(TRANSMITTED,simTime); // Set the state to transmitted
                events->addModifiedEvent(*packetBeingSent); // Add that event to the event list
                hasTransmitted = true; // Set that the packet has finished transmitting
            }

            if(sendTimeRem <= 0) // Is the packet done sending?
            {
                r->receivePacket(*packetBeingSent,simTime); // Put the packet at the router.
                Packet *temp = packetBeingSent; // Delete the packet being sent from the router cache
                packetBeingSent = NULL;
                delete temp;
            }


        }

    }
}
