// Author Erik Nadel (einadel@wpi.edu) | Jacob Watson (jrwatson@wpi.edu)
#include "packet.h"
#include <vector>
#include "router.h"
#include "eventlist.h"
namespace EIN_JRW_Lab5{
  class Host
  {
  public:
    Host(EventList* e) {events = e; packetBeingSent = NULL;}
    void addPacket(Packet p){ packets.push_back(p);} // add packet to the host to send
    Packet getPacket(); // Get the next packet to send
    void sendPacket(int trans,int prop, int simTime); // send the next packet
    int getNumPackets() {return packets.size();} // Get the number of packets in the host
    void cycle(int simTime, Router* r, int trans,int prop); // perform a cycle

  private:
    std::vector<Packet> packets; // list of packets that the host will send 
    EventList *events; // event list that the host writes to
    int sendTimeRem; // time remaining for the packet being sent
    int sendTime; // time originally set to send (for transmission calculation)
    bool hasTransmitted; // boolean for whether the packet has transmitted 
    Packet *packetBeingSent; // point to the packet currently being sent
  };
}
