// Author Erik Nadel (einadel@wpi.edu) | Jacob Watson (jrwatson@wpi.edu)
#include "router.h"
#include "packet.h"
#include "eventlist.h"
#include "eventnode.h"
#include "grid.h"
#include <iostream>
#include <string>
#define ENABLEPQ 0

namespace EIN_JRW_Prog5
{

  //Jacob Watson (jrwatson@wpi.edu)
  Router::Router(EventList* e, std::string name, int id,Grid* g)
  {
    events = e;
    maxQueueSize = 0;
    this->name = name;
    packetBeingSent = NULL;
    this->nodeID = id;

    this->rDir = directionBasedOnID(id);

    simGrid = g;

    simGrid->addObject(this);

    smallPacketQueue = FCFSqueue();
    mediumPacketQueue = FCFSqueue();
    largePacketQueue = FCFSqueue();

  }


  //Jacob Watson (jrwatson@wpi.edu)
  // Send the next packet in queue to a router
  void Router::sendPacket(int simTime)
  {

        Packet p;

        if(ENABLEPQ == 0)
            p  = this->packetQueue.dequeue(); // Get the next packet to send
        else{
            // Send the smallest packet
            if(!smallPacketQueue.isEmpty())
                p = smallPacketQueue.dequeue();
            else if (!mediumPacketQueue.isEmpty())
                p = mediumPacketQueue.dequeue();
            else if (!largePacketQueue.isEmpty())
                p = largePacketQueue.dequeue();
        }


        p.route().pop(); // Pop the destination because it arrived successfully
        SimNode *nextDest  = p.route().previewPop(); // Get the next destination


        // Calculate send time based on size and prop time
        sendTimeRem = p.getSize() + p.calculatePropTime(this->getLocation(),nextDest->getLocation());
        sendTime = sendTimeRem;

        // Announce the added events
        std::cout << "[" << simTime << "] "<< " started sending(transmitting) packet from mule " << this->getID() << std::endl;


        p.setState(TRANSMITTED,simTime+p.getSize());
        events->addModifiedEvent(p);
        p.setState(PROPAGATED,simTime+sendTime);
        events->addModifiedEvent(p);



        packetBeingSent = new Packet(); // reset the packetBeing Sent
        hasTransmitted = false;

        *packetBeingSent = p; // Set the packet being sent


  }
//Jacob Watson (jrwatson@wpi.edu)
  // Receive a packet
  void Router::receivePacket(Packet p,int simTime)
  {

        // Put the packet on the queue
        if(ENABLEPQ == 0) // is priority queue on?
            packetQueue.enqueue(p);
        else
        {
            // Put the packet in a queue according to its size
            if(p.getSize() == 1)
                smallPacketQueue.enqueue(p);
            else if(p.getSize() == 2)
                mediumPacketQueue.enqueue(p);
            else if(p.getSize() >= 3)
                largePacketQueue.enqueue(p);
        }


        p.setState(RECIEVED,simTime); // It has also been received (implied with being propagated)
        events->addModifiedEvent(p);

  }
//Jacob Watson (jrwatson@wpi.edu)
  void Router::cycle(int simTime)
  {
        // Is there a packet that is supposed to arrive here?
        while(events->hasRelevantEvent(simTime,PROPAGATED,this))
        {
            // Receive it
            EventNode* nextEvent = events->getNextRelevantEvent(simTime,PROPAGATED,this);
            Packet received = nextEvent->getData();

            std::cout << "[" << simTime << "] "<< " packet arrived/propagated at mule " << this->getID() << std::endl;

            this->receivePacket(received,simTime);
        }

        // Is the queue the largest is has ever been?
        if(packetQueue.sizeOf() > maxQueueSize) // Is the queue the biggest it has been?
        {
            maxQueueSize = packetQueue.sizeOf();
        }


        if(packetBeingSent == NULL)// Is there a packet being sent?
        {
            if(ENABLEPQ == 0)
            {
                // Do we have another packet to send?
                if(!packetQueue.isEmpty())
                {
                    sendPacket(simTime);
                }
            }
            else
            {
                if(!smallPacketQueue.isEmpty() || !mediumPacketQueue.isEmpty() || !largePacketQueue.isEmpty())
                    sendPacket(simTime);
            }
        }

        // Remove received events (they have already been processed
        if(events->hasRelevantEvent(simTime,RECIEVED,this))
            events->getNextRelevantEvent(simTime,RECIEVED,this);

        if(packetBeingSent != NULL) // Is there a packet being sent?
        {
            sendTimeRem--;

            if(sendTimeRem < sendTime - packetBeingSent->getSize() && !hasTransmitted) // Has the packet finished transmitting?
            {
                hasTransmitted = true; // Set that the packet has finished transmitting
                // No longer busy sending
                events->getNextRelevantEvent(simTime,TRANSMITTED,packetBeingSent->route().previewPop());
                std::cout << "[" << simTime << "] "<< " packet transmitted from mule " << this->getID() << std::endl;
                Packet *temp = packetBeingSent;
                packetBeingSent = NULL;
                delete temp;
            }

        }
        // Move the router every second
        if(simTime != 0 && simTime % 10 == 0)
        {
            simGrid->moveRouter(this);
        }
  }


  //Jacob Watson (jrwatson@wpi.edu)
  void Router::setDirection(Direction dir)
  {
        this->rDir = dir;
  }

  //Jacob Watson (jrwatson@wpi.edu)
  void Router::setLocation(location newLoc)
  {
        this->nodeLoc = newLoc;
  }

  //Jacob Watson (jrwatson@wpi.edu)
  Direction Router::getDirection()
  {
        return this->rDir;
  }

    //Jacob Watson (jrwatson@wpi.edu)
  location Router::getLocation()
  {
        return this->nodeLoc;
  }
    //Jacob Watson (jrwatson@wpi.edu)
  int Router::getID()
  {
    return this->nodeID;
  }

   //Jacob Watson (jrwatson@wpi.edu)
  Direction Router::directionBasedOnID(int id)
  {
        int direction = id % 4;
        switch (direction)
        {
            case 0:
                return NORTH;
            case 1:
                return EAST;
            case 2:
                return SOUTH;
            case 3:
                return WEST;
        }
        return NORTH;
  }
  //Jacob Watson (jrwatson@wpi.edu)
    void Router::identifyType()
    {
        std::cout << "Router " << std::endl;
    }
}
