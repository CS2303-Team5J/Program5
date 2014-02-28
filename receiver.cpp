// Author Erik Nadel (einadel@wpi.edu)
#include "packet.h"
#include <iostream>
#include "receiver.h"
#include "eventlist.h"
#include "eventnode.h"


namespace EIN_JRW_Prog5
{
	Receiver::Receiver(EventList* e)
	{
        this->events = e;
        numPacketsReceived = 0;
		totalResponseTime = 0;
	}

	void Receiver::receivePacket(Packet p, int simTime)
	{
		p.setState(PROPAGATED,simTime); // The packet is at the router (it was propegated)
		events->addModifiedEvent(p);
		p.setState(DELIVERED,simTime); // This means that the router was also delivered
		p.setReceived(simTime); // Set the received time
		events->addModifiedEvent(p); // Add to the event list
		numPacketsReceived++;
		printPacketStatistics(p);
		totalResponseTime += p.getResponseTime();
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
}
