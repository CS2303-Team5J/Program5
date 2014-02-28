#ifndef SIMNODE_H
#define SIMNODE_H
#include "location.h"
#include "packet.h"
namespace EIN_JRW_Prog5
{
    class SimNode
    {
        public:
            int getID();
            location getLocation();
            void setLocation(location l);
            void receivePacket(Packet p,int simTime);

        protected:
            int nodeID;
            location nodeLoc;
    };
}
#endif
