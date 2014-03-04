
#include "eventnode.h"
#include "eventlist.h"
#include "packet.h"
#include <iostream>

namespace EIN_JRW_Prog5
{
    //Author Erik Nadel (einadel@wpi.edu)
	EventList::EventList()
	{
		head = NULL;
	}

    //Author Erik Nadel (einadel@wpi.edu)
    // Add a new event to the event list
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
	    	tail = head;
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
	    	// Update the tail
	    	cursor = head;
	    	while(cursor!= NULL)
	    	{
                cursor = cursor->link();
	    	}
	    	tail = cursor;
	    }
	}
    //Author Erik Nadel (einadel@wpi.edu)
	// Add a modified existing event to the event list
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

	    	while(cursor != NULL && (p.getModifiedTime() >= cursor->getData().getArrivalTime() && p.getModifiedTime() >= cursor->getData().getModifiedTime()))
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
	//Author Erik Nadel (einadel@wpi.edu) | mixed with some code from http://runnable.com/Us53QO5op1hWAACi/how-to-remove-a-node-from-a-linked-list-for-c%2B%2B
	// Gets the next event on the event list if it is relevant to the parameters given
	EventNode* EventList::getNextRelevantEvent(int time, state s, SimNode* curr)
	{

        EventNode *cursor = NULL;
        EventNode *toDelete = NULL;
        EventNode *relevant = new EventNode();

        // Is the head what we are looking for?
        if (head->getData().getModifiedTime() <= time &&
            head->getData().getState() == s &&
            head->getData().route().previewPop() == curr)
        {
            // Delete and return what was at the head
            *relevant = *head;
            relevant->getData().route() = head->getData().route();
            toDelete = head;
            head = toDelete->link();
            delete toDelete;
            return relevant;
        }

        cursor = head;
        toDelete = head->link();

        // Traverse until something comes up
        while (toDelete != NULL) {
            if (toDelete->getData().getModifiedTime() <= time &&
                toDelete->getData().getState() == s &&
                toDelete->getData().route().previewPop() == curr)
            {
                // If something comes up, delete and return what was there
                *relevant = *toDelete;
                relevant->getData().route() = toDelete->getData().route();

                cursor->link() = toDelete->link();

                if (toDelete == tail) {
                    tail = cursor;
                }

                delete toDelete;
                return relevant;
            }
            cursor = toDelete;
            toDelete = toDelete->link();
        }
        // Nothing was taken out
        // Didnt find anything
        return NULL;
	}

    //Author Erik Nadel (einadel@wpi.edu)
    // Does the eventlist have anything needed by the parameters?
	bool EventList::hasRelevantEvent(int time, state s, SimNode* curr)
	{
        EventNode* cursor = head;
        while(cursor!= NULL)
        {
            if(cursor->getData().getModifiedTime() <= time &&
                cursor->getData().getState() == s &&
                cursor->getData().route().previewPop() == curr)
                {
                    return true;
                }
            cursor = cursor->link();
        }
        return false;
	}


	// Print out the event list
    //Author Erik Nadel (einadel@wpi.edu)
	void EventList::printEventList()
	{
        EventNode *cursor = head;
        while(cursor != NULL)
        {
            std::cout << "Arrived: " << cursor->getData().getArrivalTime() << " ";
            std::cout << "Modified: " << cursor->getData().getModifiedTime() << " ";
            std::cout << "Going to " << cursor->getData().route().previewPop() << " ";
            std::cout << "FROM : " <<cursor->getData().getSource() << " ";
            std::cout << "STATE: ";
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

    // Is the event list empty?
    //Author Erik Nadel (einadel@wpi.edu)
	bool EventList::isEmpty()
	{
        return head == NULL;
	}

}
