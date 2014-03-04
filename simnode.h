#ifndef SIMNODE_H
#define SIMNODE_H
#include "location.h"
//Author: Erik Nadel (einadel@wpi.edu) | Jacob Watson (jrwatson@wpi.edu)

#include "packet.h"
#include <iostream>

namespace EIN_JRW_Prog5
{
    class SimNode
    {
        public:
            int getID();
            virtual location getLocation();
            void setLocation(location l);

            // Methods that are used for all nodes
                // Receive a packet at the node
            virtual void receivePacket(Packet p,int simTime) {}
                // Run its cycle to check what events it needs to process in that simtime
            virtual void cycle(int simTime) {}
                // Set the arrival time of the simnode (only used on hosts)
            virtual void setArrivalTime(int time) {}
                // Get the arrival time of a simnode (0 by default because only hosts have one greater than 0)
            virtual int getArrivalTime() {return 0;}
                // Add a packet to the simnode (for hosts)
            virtual void addPacket(Packet p) {}
                // Get the average response time (for receivers)
            virtual double getAverageResponseTime() {return -1.0;}
                // Get the max queue size (for mules)
            virtual int getMaxQueue() {return -1;}
                // Identify the type of simnode ("router","host","receiver")
            virtual void identifyType() {std::cout << "Not defined" << std::endl;}
                // Number crunch the packet stats (for receiver)
            virtual void processPacketStats() {}
                // Get the total number of packets received (receiver)
            virtual int getNumPacketsReceived() {return 0;}
                // Get the total response time (receiver)
            virtual int getTotalResponseTime() {return 0;}
                // Get the average variance of all the senders of a receiver (used for receiver)
            virtual double getAverageVariance() {return -1;}

        protected:
            int nodeID;
            location nodeLoc;
    };
}
#endif
