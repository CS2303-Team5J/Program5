// Author Erik Nadel (einadel@wpi.edu)
#ifndef RECEIVER_H
#define RECEIVER_H
#include "eventlist.h"
#include "simnode.h"
namespace EIN_JRW_Prog5
{
    class Receiver : public SimNode
	{
 	public:
	// Constructors
		Receiver(EventList* e);
	//////
		void receivePacket(Packet p, int simTime); // Receive a packet
		void printPacketStatistics(Packet p); // Print the packet stats
		int getNumPacketsReceived(){return numPacketsReceived;} // Print num packets received
		double getAverageResponseTime();
 	private:
		int prop;
		int numPacketsReceived;
		int totalResponseTime;
		EventList *events;
	};
}
#endif
