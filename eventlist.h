// Author Erik Nadel (einadel@wpi.edu) | Jacob Watson (jrwatson@wpi.edu)
#ifndef EVENTLIST_H
#define EVENTLIST_H
#include "packet.h"
#include "eventnode.h"

namespace EIN_JRW_Prog5
{
	class EventList
	{
	public:
            EventList(); //constructor

	    	void addNewEvent(Packet p); //adds a event/packet to the list
    		void addModifiedEvent(Packet p); // adds an updated event to the list
    		EventNode* getNextRelevantEvent(int time,state s, SimNode *currNode); // Get the next relevant event at the current time

    		bool hasRelevantEvent(int time, state s, SimNode *currNode); // Is the next event relevant to currNode?
    		EventNode peakNextEvent(); // What is the next event? (dont take it off)
    		bool isEmpty(); // Is the event list empty?
    		void printEventList(); // Print the event list
	    private:
            EventNode* head; // The start of the event list
            EventNode* tail; // end of event list
  	};
}
#endif
