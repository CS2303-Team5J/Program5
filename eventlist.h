// Author Erik Nadel (einadel@wpi.edu)
#ifndef EVENTLIST_H
#define EVENTLIST_H
#include "packet.h" //includes packet header
#include "eventnode.h"

namespace EIN_JRW_Lab5
{
	class EventList
	{
	public:
		EventList(); //constructor
	    	void addNewEvent(Packet p); //adds a event/packet to the list
    		void addModifiedEvent(Packet p); // adds an updated event to the list
    		EventNode getNextEvent(); // Gets the next event
    		void printEventList(); // Print the event list 
	    private:
  		EventNode* head; // The start of the event list
  	};
}
#endif
