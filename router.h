// Author Jacob Watson (jrwatson@wpi.edu)
#ifndef ROUTER_H
#define ROUTER_H
#include "FCFSqueue.h"
#include "receiver.h"
#include "router.h"
#include "eventlist.h"
#include <string>
namespace EIN_JRW_Lab5
{
class Router
{
 public:
  // Constructor
  Router(EventList* e, std::string name){ events = e; maxQueueSize = 0; this->name = name; packetBeingSent = NULL;}
	// Send the packet
  void sendPacket(int simTime, int trans, int prop);
	// Receive a packet
  void receivePacket(Packet p, int simTime);
	// Get the name of the router
  std::string getName(){return this->name;}
	// Run a cycle for sending a packet to another router
  void cycle(int simTime,Router* r, int trans, int prop);
	// Run a cycle for sending a packet to a receiver 
  void cycle(int simTime,Receiver* r, int trans, int prop);
	// Get the max queue size experienced
  int getMaxQueue() { return maxQueueSize;}

 private:
  FCFSqueue packetQueue;
  EventList *events;
  Packet *packetBeingSent;
  int sendTimeRem;
  int sendTime;
  bool hasTransmitted;
  int maxQueueSize;
  std::string name;

};
}
#endif