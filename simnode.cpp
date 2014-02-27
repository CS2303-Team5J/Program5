#include "simnode.h"

namespace EIN_JRW_Prog5
{
    location SimNode::getLocation()
    {
        return this->nodeLoc;
    }

    void SimNode::setLocation(location l)
    {
        this->nodeLoc = l;
    }

}
