// Author Erik Nadel (einadel@wpi.edu)
#ifndef RECEIVER_H
#define RECEIVER_H
#include "eventlist.h"
#include "simnode.h"

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
		void printPacketStatistics(Packet p); // Print the packet stats
		int getNumPacketsReceived(){return numPacketsReceived;} // Print num packets received
		double getAverageResponseTime();
		location getLocation();
 	private:
		int prop;
		int numPacketsReceived;
		int totalResponseTime;
		EventList *events;
		Grid *simGrid;
		int gridSize;
	};
}
#endif
