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

    simGrid->addObject(this);

  }


  // Send the next packet in queue to a router
  void Router::sendPacket(int simTime)
  {
        Packet p  = this->packetQueue.dequeue(); // Get the next packet to send
        //events->addNewEvent(p); // Add to the event list that the packet arrived
        p.route().pop();
        SimNode *nextDest  = p.route().previewPop();


        sendTimeRem = p.getSize() + p.calculatePropTime(this->getLocation(),nextDest->getLocation());
        sendTime = sendTimeRem;

        p.setState(TRANSMITTED,simTime+p.getSize());
        events->addModifiedEvent(p);
        p.setState(PROPAGATED,simTime+sendTime);
        events->addModifiedEvent(p);



        packetBeingSent = new Packet(); // reset the packetBeing Sent
        hasTransmitted = false;

        *packetBeingSent = p; // Set the packet being sent

    //r->receivePacket(p,events,simTime);
  }
  // Receive a packet
  void Router::receivePacket(Packet p,int simTime)
  {

        //p.route().pop(); // Packet made it to destination. Remove it
        packetQueue.enqueue(p);
        //packetQueue.printQueue();

        events->getNextRelevantEvent(simTime,PROPAGATED,this);
        p.setState(RECIEVED,simTime); // It has also been received (implied)
        events->addModifiedEvent(p);
        //std::cout << "- - - " << std::endl;
        //events->printEventList();
        //std::cout << name << ": "; // print the packet name for debugging
        //packetQueue.printQueue();

  }
  void Router::cycle(int simTime)
  {

        if(events->hasRelevantEvent(simTime,PROPAGATED,this))
        {
            EventNode* nextEvent = events->getNextRelevantEvent(simTime,PROPAGATED,this);
            Packet received = nextEvent->getData();
            //std::cout << "received packet " << std::endl;

            //std::cout << "with destination " << std::cout << received.route().previewPop() << std::endl;
            //printPath();
            //std::cout << received.route().getSize() << std::endl;
            //events->printEventList();
            this->receivePacket(received,simTime);
        }

        if(packetQueue.sizeOf() > maxQueueSize) // Is the queue the biggest it has been?
        {
            maxQueueSize = packetQueue.sizeOf();
        }
        if(packetBeingSent == NULL)// Is there a packet being sent?
        {
            // Do we have another packet to send?
            if(!packetQueue.isEmpty())
            {
                sendPacket(simTime);
            }
        }


        if(events->hasRelevantEvent(simTime,RECIEVED,this))
            events->getNextRelevantEvent(simTime,RECIEVED,this);

        if(packetBeingSent != NULL) // Is there a packet being sent?
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

//            if(sendTimeRem <= sendTime - packetBeingSent->getSize() && !hasTransmitted) // Has the packet transmitted?
//            {
//                packetBeingSent->setState(TRANSMITTED,simTime); // Mark transmitted
//                events->addModifiedEvent(*packetBeingSent); // add to event list
//                Packet *temp = packetBeingSent;
//                hasTransmitted = true;
//                packetBeingSent = NULL;
//                delete temp;
//
//            }

//            if(sendTimeRem <= 0) // Is the packet done sending?
//            {
//                SimNode *nextDest = packetBeingSent->route().previewPop();
//                nextDest->receivePacket(*packetBeingSent,simTime); // make sure the router has the packet
//                Packet *temp = packetBeingSent; // delete packet from cache
//                packetBeingSent = NULL;
//                delete temp;
//            }
        }
        if(simTime != 0 && simTime % 10 == 0)
        {
            simGrid->moveRouter(this);
            //simGrid->print();
        }
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
