// Author Erik Nadel (einadel@wpi.edu)
#include "packet.h"
#include <iostream>
#include "receiver.h"
#include "eventlist.h"
#include "eventnode.h"
#include "grid.h"
#include "senderStats.h"


namespace EIN_JRW_Prog5
{
// Author Erik Nadel (einadel@wpi.edu
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
// Author Erik Nadel (einadel@wpi.edu
	void Receiver::receivePacket(Packet p, int simTime)
	{
		p.setState(DELIVERED,simTime); // This means that the router was also delivered
		p.setReceived(simTime); // Set the received time
		events->addModifiedEvent(p); // Add to the event list

		numPacketsReceived++;

        std::cout << "[" << simTime << "] "<< " packet delivered to receiver "  << this->getID() << std::endl;

		processPacket(p);
		totalResponseTime += p.getResponseTime();
	}
// Author Erik Nadel (einadel@wpi.edu
	void Receiver::cycle(int simTime)
	{
        // Is the next event relevant to this receiever?
        if(events->hasRelevantEvent(simTime,PROPAGATED,this))
        {
            // Get it and process it
            EventNode* nextEvent = events->getNextRelevantEvent(simTime,PROPAGATED,this);
            Packet received = nextEvent->getData();

            this->receivePacket(received,simTime);
        }

        // Remove DELIVERED events
        if(events->hasRelevantEvent(simTime,DELIVERED,this))
            events->getNextRelevantEvent(simTime,DELIVERED,this);

        //events->printEventList();
	}
// Author Erik Nadel (einadel@wpi.edu
	double Receiver::getAverageVariance()
	{
        return totalVariance / (double)numPacketsReceived;
	}
// Author Erik Nadel (einadel@wpi.edu
    // Number crunch the  stats from  each host
	void Receiver::processPacketStats()
	{

        std::cout << std::endl;
        std::cout << "Receiver: " <<  this->getID() << " got " << numPacketsReceived <<  " packets " << std::endl;
        std::cout << "-------------------------------------------" << std::endl;
        for(size_t x = 0; x < stats.size(); ++x)
        {
            std::cout << stats[x].getNumPackets();
            std::cout << " packets from host " << stats[x].getStatSenderID() << " ";
            std::cout << "w/ avg response time " << stats[x].getAvgResponseTime()/ 1000.0 << " seconds ";
            std::cout <<  "and variance of " << stats[x].calculateVariance() / 1000.0 << " seconds " << std::endl;
            totalVariance += stats[x].calculateVariance();
        }

        std::cout << "mean delay of all " << numPacketsReceived << " packets received " << getAverageResponseTime() /1000.0 << " seconds"<< std::endl;
        std::cout << "variance of the mean response time was " << getAverageVariance() / 1000.0 << " seconds "<< std::endl;


	}
// Author Erik Nadel (einadel@wpi.edu
	// Get the average response time
	double Receiver::getAverageResponseTime()
	{
		if(numPacketsReceived != 0)
			return (double) totalResponseTime / (double)numPacketsReceived;
		else
			return 0.0;
	}

// Author Erik Nadel (einadel@wpi.edu
    // Get the location of the receiver
	location Receiver::getLocation()
	{
        return location(this->nodeLoc.GetxCoord(),gridSize+1);
	}
// Author Erik Nadel (einadel@wpi.edu
    // Are we already keeping track of a specified host?
	bool Receiver::hasSender(int ID)
	{
        if(!stats.empty())
            for(size_t x = 0; x < stats.size(); ++x)
            {
                if(stats[x].getStatSenderID() == ID)
                {
                    return true;
                }
            }
        return false;
	}
// Author Erik Nadel (einadel@wpi.edu
    // Determine where the packet came from and count it
	void Receiver::processPacket(Packet p)
	{
        // Have we started recording the source?
        if(!hasSender(p.getSource()))
        {
            // Add the source to the stats
            stats.push_back(SenderStats(p.getSource()));
            stats.back().addPacket(p.getResponseTime());
        }
        else // Add that we got another packet from a host
        {
            for(size_t x = 0; x < stats.size(); ++x)
            {
                if(stats[x].getStatSenderID() == p.getSource())
                {
                    stats[x].addPacket(p.getResponseTime());
                }
            }
        }
	}


}
