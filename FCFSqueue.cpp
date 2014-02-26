// Author: Jacob Watson (jrwatson@wpi.edu) (entire file)
#include "FCFSqueue.h"
#include <iostream>
namespace EIN_JRW_Lab5
{
	void FCFSqueue::enqueue(Packet p)
	{
		QueueNode *newPtr = new QueueNode(p);
		if(newPtr != NULL) //makes sure memory space is available
		{
			if(headPtr == NULL) //if empty, insert node at head
			{
				headPtr = newPtr;
				tailPtr = newPtr;
			}
			else
			{
				tailPtr->link() = newPtr; //if not empty, insert node at end of queue
				tailPtr = newPtr; // Change tail to point to new end
			}
			numElements++;
		}
	}

  Packet FCFSqueue::dequeue()
  {
    QueueNode* tempPtr = headPtr;
    headPtr = headPtr->link(); // Change head to next in the queue
    if(headPtr == NULL) // Is the list empty now?
    {
		tailPtr = NULL; // Make sure tail points to nothing then.
    }
    Packet temp = tempPtr->getContents();
    tempPtr->link() = NULL;
    delete tempPtr;
    numElements--;
    return temp;

  }

  bool FCFSqueue::isEmpty()
  {
    return headPtr == NULL;
  }

  void FCFSqueue::printQueue()
  {
    QueueNode *cursor = headPtr;
    do
    {
        std::cout << cursor->getContents().getSize(); // Print out the packet size (for debug id)
        cursor = cursor->link(); // Get the next packet
        if(cursor != NULL) // Dont print the cursor on the last node
            std::cout <<  "<-- ";
    } while (cursor != NULL);
    std::cout << std::endl;
  }


}
