// Author Jacob Watson (jrwatson@wpi.edu) | Erik Nadel (einadel@wpi.edu)
#ifndef ROUTER_H
#define ROUTER_H
#include "FCFSqueue.h"
#include "receiver.h"
#include "router.h"
#include "eventlist.h"
#include "location.h"
#include "grid.h"
#include "simnode.h"

#include <string>
namespace EIN_JRW_Prog5
{
class Grid;
class Router : public SimNode
{
 public:
  // Constructor
  Router(EventList* e, std::string name, int id,Grid* g);
	// Send the packet
  void sendPacket(int simTime);
	// Receive a packet
  void receivePacket(Packet p, int simTime);
	// Get the name of the router
  std::string getName(){return this->name;}
	// Run a cycle for sending a packet to another node
  void cycle(int simTime);
	// Get the max queue size experienced
  int getMaxQueue() { return maxQueueSize;}
    // Get the location of the router
  location getLocation();
    // Get the ID of the router
  int getID();
    // Get the direction of the router
  Direction getDirection();
    // Set the direction of the router
  void setDirection(Direction dir);
    // Set the location of the router
  void setLocation(location newLoc);
    // identify that this is a router
  void identifyType();

 private:

    // Generate a direction based on the id
  Direction directionBasedOnID(int id);

  FCFSqueue packetQueue;
  FCFSqueue smallPacketQueue;
  FCFSqueue mediumPacketQueue;
  FCFSqueue largePacketQueue;
  EventList *events;
  Packet *packetBeingSent;
  int sendTimeRem;
  int sendTime;
  bool hasTransmitted;
  int maxQueueSize;
  std::string name;
  Direction rDir;
  Grid *simGrid;
};
}
#endif
