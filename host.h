// Author Erik Nadel (einadel@wpi.edu) | Author Jacob Watson (jrwatson@wpi.edu)
#include "packet.h"
#include <vector>
#include "router.h"
#include "eventlist.h"
#include <iostream>
namespace EIN_JRW_Prog5{

  class Grid;
  class Host : public SimNode
  {
  public:
    Host(EventList* e,int id,Grid* g);

    // Author Erik Nadel (einadel@wpi.edu)
    void addPacket(Packet p){packets.push_back(p);} // add packet to the host to send

    //Author Jacob Watson (jrwatson@wpi.edu)
    Packet getPacket(); // Get the next packet to send

    // Author Erik Nadel (einadel@wpi.edu)
    void sendPacket(int simTime); // send the next packet

    //Author Jacob Watson (jrwatson@wpi.edu)
    int getNumPackets() {return packets.size();} // Get the number of packets in the host

    // Author Erik Nadel (einadel@wpi.edu)
    void cycle(int simTime); // perform a cycle

    //Author Jacob Watson (jrwatson@wpi.edu)
    location getLocation(); // Get the location of the host

    // Author Erik Nadel (einadel@wpi.edu)
    int getPacketsSent() {return packetsSent;} // Get the number of packets sent from the host

    //Author Jacob Watson (jrwatson@wpi.edu)
    void setArrivalTime(int time){arrivalTime = time;} // set the arrival time of the host

    // Author Erik Nadel (einadel@wpi.edu)
    int getArrivalTime() {return arrivalTime;} // Get the arrival time of the host

    //Author Jacob Watson (jrwatson@wpi.edu)
    void identifyType() {std::cout << "Host " << std::endl;} // Identify self as host


  private:
    std::vector<Packet> packets; // list of packets that the host will send
    EventList *events; // event list that the host writes to
    int sendTimeRem; // time remaining for the packet being sent
    int sendTime; // time originally set to send (for transmission calculation)
    bool hasTransmitted; // boolean for whether the packet has transmitted
    Packet *packetBeingSent; // point to the packet currently being sent
    Grid *simGrid;
    int packetsSent;
    int arrivalTime;
  };
}
