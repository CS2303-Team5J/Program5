// Author: Erik Nadel (einadel@wpi.edu) (entire file)
#include "eventnode.h"
#include "eventlist.h"
#include "packet.h"
#include <iostream>

namespace EIN_JRW_Prog5
{
	EventList::EventList()
	{
		head = NULL;
	}

	void EventList::addNewEvent(Packet p)
	{
		EventNode* cursor;
	    EventNode* previousPtr;
	    EventNode* newNode = new EventNode(p);
	    // Is the list empty?
	    if (head == NULL)
	    {
	    	// Start the list.
	    	head = newNode;
	    }
	    else
	    {
	    	cursor = head;
	    	previousPtr = NULL;

	    	while(cursor != NULL && p.getArrivalTime() >= cursor->getData().getArrivalTime())
	    	{
	    		// Walk to next node
	    		previousPtr = cursor;
	    		cursor = cursor->link();
	    	}
	    	// Do we need to insert at the head?
	    	if(previousPtr == NULL)
	    	{
	    		newNode->link() = head;
	    		head = newNode;
	    	}
	    	else
	    	{
	    		previousPtr->link() = newNode;
	    		newNode->link() = cursor;
	    	}
	    }
	}
	void EventList::addModifiedEvent(Packet p)
	{
        EventNode* cursor;
	    EventNode* previousPtr;
	    EventNode* newNode = new EventNode(p);
	    // Is the list empty?
	    if (head == NULL)
	    {
	    	// Start the list.
	    	head = newNode;
	    }
	    else
	    {
	    	cursor = head;
	    	previousPtr = NULL;

	    	while(cursor != NULL && (p.getModifiedTime() >= cursor->getData().getArrivalTime() || p.getModifiedTime() >= cursor->getData().getModifiedTime()))
	    	{
	    		// Walk to next node
	    		previousPtr = cursor;
	    		cursor = cursor->link();
	    	}
	    	// Do we need to insert at the head?
	    	if(previousPtr == NULL)
	    	{
	    		newNode->link() = head;
	    		head = newNode;
	    	}
	    	else
	    	{
	    		previousPtr->link() = newNode;
	    		newNode->link() = cursor;
	    	}
	    }
	}
	// Gets the next event on the event list
	EventNode EventList::getNextEvent()
	{
	        EventNode *temp = head;
	        head = head->link(); // Sets head to next link
	        EventNode tempNode = *temp;
	        temp->link() = NULL;
	        delete temp;
	        return tempNode;
	}
	// Print out the event list
	void EventList::printEventList()
	{
        EventNode *cursor = head;
        while(cursor != NULL)
        {
            std::cout << cursor->getData().getSize() << ": ";
	    // Print out the status of the packet.
            switch (cursor->getData().getState())
            {
                case RECIEVED:
                    std::cout << "RECEIVED" << std::endl;
                    break;
                case TRANSMITTED:
                    std::cout << "TRANSMITTED" << std::endl;
                    break;
                case DELIVERED:
                    std::cout << "DELIVERED" << std::endl;
                    break;
                case ARRIVED:
                    std::cout << "ARRIVED" << std::endl;
                    break;
                case PROPAGATED:
                    std::cout << "PROPAGATED" << std::endl;
                    break;

            }
            cursor = cursor->link();
        }
	}
}
