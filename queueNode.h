// Jacob Watson (jrwatson@wpi.edu) (entire file)
#ifndef QUEUENODE_H
#define QUEUENODE_H
#include "packet.h"


namespace EIN_JRW_Prog5
{
  class QueueNode{ //this class makes up the contents of the queue and holds the packets within it
  public:
	QueueNode(Packet p) {contents = p; nextPtr = NULL;}
	// Modification Functions
    void setContents(Packet p){contents = p;} //sets the contents of the node
    QueueNode*& link() {return nextPtr;} //Returns a reference to the link to set the next node
    // Constant functions
    QueueNode getNextPtr() {return (*nextPtr);} //returns the nodes next ptr
    Packet getContents() {return (contents);} //returns the contents of the node
  private:
    Packet contents; //points to the packet being stored in the node
    QueueNode *nextPtr; //points to the next node in the queue
  };
}

#endif
