#include "packet.h"
#include <string>
#include <cmath>
#include <vector>
#include <cstdlib>

namespace EIN_JRW_Prog5
{
    // Author Jacob Watson (jrwatson@wpi.edu)
    Packet::Packet(int numBits, int source, state initState, int arrival)
    {
        bitSize = numBits;
        this->source = source;
        currentState = initState;
        arrived = arrival;
        this->timeReceived = timeReceived;
        timeModified = 0;
        sourceRoute = Queue<SimNode*>();
    }

// Author Jacob Watson (jrwatson@wpi.edu)

    // Get the route of a packet
    Queue<SimNode*>& Packet::route()
    {
        return this->sourceRoute;
    }

// Author Jacob Watson (jrwatson@wpi.edu)
    // Calculate the log(2) of a number
    double logbase2(double num)
    {
        // Using a property of logarithms, we are able to calculate log(2) with the traditional log(10)
        return log10(num) / log10(2);
    }

// Author Jacob Watson (jrwatson@wpi.edu)
    // Calculates the Euclidiean distance between two points
    double distance(int x1, int y1, int x2, int y2)
    {
        double result = sqrt(pow(x2-x1,2) + pow(y2-y1,2));
        return result;
    }

// Author Jacob Watson (jrwatson@wpi.edu)
    // Calculate the propegation time of a packet between two destinations
    int Packet::calculatePropTime(location start, location endPoint)
    {
        if(start.GetxCoord() == endPoint.GetxCoord() && start.GetyCoord() == endPoint.GetyCoord())
        {
            return 0; // Not supposed to happen
        }
        return (int) ceil(logbase2(distance(start.GetxCoord(),start.GetyCoord(),
                                      endPoint.GetxCoord(),endPoint.GetyCoord())));
    }
// Author Jacob Watson (jrwatson@wpi.edu)
    // Print the path of the packet
    void Packet::printPath()
    {
        sourceRoute.printData();
    }
// Author Jacob Watson (jrwatson@wpi.edu)
    // Set the path of the packet
    void Packet::setPath(Queue<SimNode*> networkPath)
    {
        sourceRoute = networkPath;
    }


}
