#ifndef SIMNODE_H
#define SIMNODE_H
#include "location.h"
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
            virtual void receivePacket(Packet p,int simTime) {}
            virtual void cycle(int simTime) {}
            virtual void setArrivalTime(int time) {}
            virtual int getArrivalTime() {return 0;}
            virtual void addPacket(Packet p) {}
            virtual double getAverageResponseTime() {return -1.0;}
            virtual int getMaxQueue() {return -1;}
            virtual void identifyType() {std::cout << "Not defined" << std::endl;}

        protected:
            int nodeID;
            location nodeLoc;
    };
}
#endif
