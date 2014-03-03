// Author Erik Nadel (einadel@wpi.edu)
#include "packet.h"
#include <iostream>
#include "receiver.h"
#include "eventlist.h"
#include "eventnode.h"
#include "grid.h"


namespace EIN_JRW_Prog5
{
	Receiver::Receiver(EventList* e,int id,Grid* onGrid,int rGridSize)
	{
        this->events = e;
        numPacketsReceived = 0;
		totalResponseTime = 0;
		this->nodeID = id;
		simGrid = onGrid;
        gridSize = rGridSize;
        simGrid->addObject(this);
	}

	void Receiver::receivePacket(Packet p, int simTime)
	{
        //p.route().pop();
//		p.setState(PROPAGATED,simTime); // The packet is at the router (it was propegated)
//		events->addModifiedEvent(p);
		p.setState(DELIVERED,simTime); // This means that the router was also delivered
		p.setReceived(simTime); // Set the received time
		events->addModifiedEvent(p); // Add to the event list
		numPacketsReceived++;
		printPacketStatistics(p);
		totalResponseTime += p.getResponseTime();
	}

	void Receiver::cycle(int simTime)
	{
        if(events->hasRelevantEvent(simTime,PROPAGATED,this))
        {
            EventNode* nextEvent = events->getNextRelevantEvent(simTime,PROPAGATED,this);
            Packet received = nextEvent->getData();
            std::cout << "Receiver received packet " << std::endl;
            this->receivePacket(received,simTime);
        }

        if(events->hasRelevantEvent(simTime,DELIVERED,this))
            events->getNextRelevantEvent(simTime,DELIVERED,this);
	}

	void Receiver::printPacketStatistics(Packet p)
	{
		std::cout << "Packet from " << p.getSource() << std::endl;
		std::cout << "Response time " << p.getResponseTime() << std::endl;
	}
	double Receiver::getAverageResponseTime()
	{
		if(numPacketsReceived != 0)
			return totalResponseTime / numPacketsReceived;
		else
			return 0.0;
	}

	location Receiver::getLocation()
	{
        return location(this->nodeLoc.GetxCoord(),gridSize+1);
	}
}
