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

        protected:
            int nodeID;
            location nodeLoc;
    };
}
#endif
