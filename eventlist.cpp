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
	// Gets the next event on the event list
	EventNode* EventList::getNextRelevantEvent(int time, state s, SimNode* curr)
	{

        EventNode *pPre = NULL, *pDel = NULL;
        EventNode *relevant = new EventNode();

        /* Check whether it is the head node?
        if it is, delete and update the head node */
        if (head->getData().getModifiedTime() <= time &&
            head->getData().getState() == s &&
            head->getData().route().previewPop() == curr)
        {
            /* point to the node to be deleted */
            *relevant = *head;
            relevant->getData().route() = head->getData().route();
            pDel = head;
            /* update */
            head = pDel->link();
            delete pDel;
            return relevant;
        }

        pPre = head;
        pDel = head->link();

        /* traverse the list and check the value of each node */
        while (pDel != NULL) {
            if (pDel->getData().getModifiedTime() <= time &&
                pDel->getData().getState() == s &&
                pDel->getData().route().previewPop() == curr)
            {
                //std::cout << pDel->getData().route().previewPop();
                //pDel->getData().printPath();
                *relevant = *pDel;
                relevant->getData().route() = pDel->getData().route();
                /* Update the list */
                pPre->link() = pDel->link();
                /* If it is the last node, update the tail */
                if (pDel == tail) {
                    tail = pPre;
                }

                delete pDel; /* Here only remove the first node with the given value */
                return relevant; /* break and return */
            }
            pPre = pDel;
            pDel = pDel->link();
//	        EventNode *temp = head;
//	        head = head->link(); // Sets head to next link
//	        EventNode tempNode = *temp;
//	        temp->link() = NULL;
//	        delete temp;
//	        return tempNode;
        }
        // Nothing was deleted
        return NULL;
	}

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

	bool EventList::isEmpty()
	{
        return head == NULL;
	}

}
