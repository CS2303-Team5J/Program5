// Author Erik Nadel (einadel@wpi.edu) (entire file)
#ifndef RECEIVER_H
#define RECEIVER_H
#include "eventlist.h"
#include "simnode.h"
#include "senderStats.h"
#include <vector>

namespace EIN_JRW_Prog5
{
    class Grid;
    class Receiver : public SimNode
	{
 	public:
	// Constructors
		Receiver(EventList* e,int id,Grid* onGrid,int rGridSize);
	//////
		void receivePacket(Packet p, int simTime); // Receive a packet
		void processPacketStats(); // Number crunch the packet stats
		void processPacket(Packet p); // Print the packet stats
		int getNumPacketsReceived(){return numPacketsReceived;} // Print num packets received
		int getTotalResponseTime() {return totalResponseTime;} // Get the total response time for dealing with the average
		double getAverageResponseTime(); // Calculate the average response time
		double getAverageVariance();
		location getLocation(); // Get the receiver location
		void cycle(int simTime); // Run its cycle of checking for relevant next events and processing them accordingly
 	private:
        bool hasSender(int ID); // Are we keeping track of this host in our stats?

		int prop;
		int numPacketsReceived;
		int totalResponseTime;
		double totalVariance;
		EventList *events;
		Grid *simGrid;
		int gridSize;
		std::vector<SenderStats> stats;
	};
}
#endif
