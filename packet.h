// Author Jacob Watson (jrwatson@wpi.edu) | Erik Nadel (einadel@wpi.edu)
#ifndef PACKET_H
#define PACKET_H

#include <string>
#include <vector>
#include "stack.h"
#include "location.h"
//#include "simnode.h"

namespace EIN_JRW_Prog5 {


   enum state {
		RECIEVED, //Recieved is at the router,
		TRANSMITTED, //Transmitted means the packet is being transmitted
		DELIVERED,  //Delivered is at the recieval point,
		ARRIVED, //Arrived means the packet has just come from the source,
		PROPAGATED //Propagated means that it has finished progagating
	};
  class SimNode;
  class Packet
  {
  public:

    // Constructors
    Packet() {} // Default constructor
    Packet(int numBits, int source, state initState, int arrival = 0);

    // Modification Functions
	// Set the state of the packet
    void setState(state s,int modTime){this->currentState = s; timeModified = modTime;}
	// Set the time the packet was received by the host
    void setReceived(int time) {this->timeReceived = time;}
	// Set the time the packet was sent
    void setArrival(int time) {this->arrived = time; this->timeModified = time;}
    // Constant Functions
	// Get the response time of the packet
    int getResponseTime() {return this->timeReceived - this->arrived;}
	// Get the time the packet changed state (was modified)
    int getModifiedTime() {return this->timeModified;}
	// Get the state of the packet
    state getState() {return this->currentState;}
	// Get the bit size of the packet
    int getSize() {return bitSize;}
	// Get the source of the packet
    int  getSource() {return this->source;}
	// Get the arrival time of the packet
    int getArrivalTime() {return arrived;}

    void setPath(Queue<SimNode*> networkNodes);

    void printPath();

    int calculatePropTime(location start, location endPoint);

    Queue<SimNode*>& route();
  private:
    int bitSize; // 1 2 or 3
    int source;
    int timeModified;
    int arrived;
    int timeReceived;
    state currentState;
    Queue<SimNode*> sourceRoute;
  };
}
#endif
