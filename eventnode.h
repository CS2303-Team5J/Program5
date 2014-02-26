// Author Erik Nadel(einadel@wpi.edu) (entire file)
#ifndef EVENTNODE_H
#define EVENTNODE_H
#include "packet.h"

namespace EIN_JRW_Lab5
{
	class EventNode
	{
	public:
		// Constructor
		EventNode(Packet p) { data = p; nodeLink = NULL;}
		// Modification function
		EventNode*& link() { return nodeLink; } // Get the link of the node
		Packet getData() {return data;} // get the data of the node\
	private:
		Packet data;
		EventNode* nodeLink;
	};
}
#endif
