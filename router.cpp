// Author Erik Nadel (einadel@wpi.edu) | Jacob Watson (jrwatson@wpi.edu)
#include "router.h"
#include "packet.h"
#include "eventlist.h"
#include "eventnode.h"
#include "grid.h"
#include <iostream>
#include <string>

namespace EIN_JRW_Prog5
{

  Router::Router(EventList* e, std::string name, int id,Grid* g)
  {
    events = e;
    maxQueueSize = 0;
    this->name = name;
    packetBeingSent = NULL;
    this->nodeID = id;

    this->rDir = directionBasedOnID(id);

    simGrid = g;

  }


  // Send the next packet in queue to a router
  void Router::sendPacket(int simTime,int trans, int prop)
  {
    Packet p = this->packetQueue.dequeue();
    sendTimeRem = trans + prop;
    sendTime = trans + prop;
    packetBeingSent = new Packet();
    hasTransmitted = false;
    *packetBeingSent = p;
    std::cout << packetQueue.sizeOf() << std::endl;


    //r->receivePacket(p,events,simTime);
  }
  // Receive a packet
  void Router::receivePacket(Packet p,int simTime)
  {
    p.setState(PROPAGATED,simTime); // A packet received means it has been propagated
    events->addModifiedEvent(p);
	packetQueue.enqueue(p);
	p.setState(RECIEVED,simTime); // It has also been received (implied)
	events->addModifiedEvent(p);
    //std::cout << name << ": "; // print the packet name for debugging
    //packetQueue.printQueue();

  }
  void Router::cycle(int simTime, Router* r,int trans, int prop)
  {

        if(packetQueue.sizeOf() > maxQueueSize) // Is the queue the biggest it has been?
        {
            maxQueueSize = packetQueue.sizeOf();
        }
        if(packetBeingSent == NULL)// Is there a packet being sent?
        {
            // Do we have another packet to send?
            if(!packetQueue.isEmpty())
            {
                sendPacket(simTime,trans,prop);
            }
        }
        if(packetBeingSent != NULL) // Is there a packet being sent?
        {
            sendTimeRem--;

            if(sendTimeRem <= sendTime-trans && !hasTransmitted) // Has the packet transmitted?
            {
                packetBeingSent->setState(TRANSMITTED,simTime); // Mark transmitted
                events->addModifiedEvent(*packetBeingSent); // add to event list
                hasTransmitted = true;
            }

            if(sendTimeRem <= 0) // Is the packet done sending?
            {
                r->receivePacket(*packetBeingSent,simTime); // make sure the router has the packet
                Packet *temp = packetBeingSent; // delete packet from cache
                packetBeingSent = NULL;
                delete temp;
            }
        }
  }
  void Router::cycle(int simTime, Receiver* r,int trans, int prop)
  {
	// Same as before. except this is a cycle to send to a receiver.

        if(packetQueue.sizeOf() > maxQueueSize)
        {
            maxQueueSize = packetQueue.sizeOf();
        }
        if(packetBeingSent == NULL)
        {
            // Do we have another packet to send?
            if(!packetQueue.isEmpty())
            {
                sendPacket(simTime,trans,prop);
            }
        }
        else if(packetBeingSent != NULL)
        {
            sendTimeRem--;
            if(sendTimeRem <= sendTime-trans && !hasTransmitted)
            {
                packetBeingSent->setState(TRANSMITTED,simTime);
                events->addModifiedEvent(*packetBeingSent);
                hasTransmitted = true;
            }
            if(sendTimeRem <= 0)
            {
                r->receivePacket(*packetBeingSent,simTime);
                Packet *temp = packetBeingSent;
                packetBeingSent = NULL;
                delete temp;
            }
        }

       if(simTime % 10 == 0 && simTime != 0)
            simGrid->moveRouter(this);


  }


  void Router::setDirection(Direction dir)
  {
        this->rDir = dir;
  }

  void Router::setLocation(location newLoc)
  {
        this->nodeLoc = newLoc;
  }

  Direction Router::getDirection()
  {
        return this->rDir;
  }

  location Router::getLocation()
  {
        return this->nodeLoc;
  }

  int Router::getID()
  {
    return this->nodeID;
  }


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

}
