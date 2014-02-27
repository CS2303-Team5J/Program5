// Author : Jacob Watson (jrwatson@wpi.edu)  (entire file)
#ifndef FCFSQUEUE_H
#define FCFSQUEUE_H
#include "packet.h"
#include "queueNode.h"
namespace EIN_JRW_Prog5
{
  class FCFSqueue //this class handles the transmission queues for M1 and M2.
{
 public:
  FCFSqueue() {numElements = 0; headPtr = NULL; tailPtr = NULL; }
  void enqueue(Packet p); //adds a packet to the queue for transmission
  Packet dequeue(); //dequeues the packet at the front of the list for transmission
  bool isEmpty(); // checks to see if the queue is empty
  void printQueue();
  int sizeOf() {return numElements;}
 private:
  QueueNode* headPtr;
  QueueNode* tailPtr;
  int numElements;
};

}
#endif
