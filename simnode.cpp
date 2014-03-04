#include "simnode.h"


namespace EIN_JRW_Prog5
{
    // Gets the current location of a simnode
    //Author: Erik Nadel (einadel@wpi.edu)
    location SimNode::getLocation()
    {
        return this->nodeLoc;
    }

    //Author: Erik Nadel (einadel@wpi.edu)
    // Sets the location of a simnode
    void SimNode::setLocation(location l)
    {
        this->nodeLoc = l;
    }

    //Author: Erik Nadel (einadel@wpi.edu)
    // Gets the id of a simnode
    int SimNode::getID()
    {
        return this->nodeID;
    }

}
