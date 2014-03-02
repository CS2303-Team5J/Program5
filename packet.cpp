#include "packet.h"
#include <string>
#include <cmath>
#include <vector>
#include <cstdlib>

namespace EIN_JRW_Prog5
{
    Packet::Packet(int numBits, std::string source, state initState, int arrival)
    {
        bitSize = numBits;
        this->source = source;
        currentState = initState;
        arrived = arrival;
        this->timeReceived = timeReceived;
        timeModified = 0;
        sourceRoute = Stack<SimNode*>();
    }

    Stack<SimNode*>& Packet::route()
    {
        return this->sourceRoute;
    }

    double logbase2(double num)
    {
        // Using a property of logarithms, we are able to calculate log(2) with the traditional log(10)
        return log10(num) / log10(2);
    }

    // Calculates the Euclidiean distance between two points
    double distance(int x1, int y1, int x2, int y2)
    {
        double result = sqrt(pow(x2-x1,2) + pow(y2-y1,2));
        return result;
    }


    int Packet::calculatePropTime(location start, location endPoint)
    {
        return ceil(logbase2(distance(start.GetxCoord(),start.GetyCoord(),
                                      endPoint.GetxCoord(),endPoint.GetyCoord())));
    }

    void Packet::printPath()
    {
        sourceRoute.printData();
    }

    void Packet::setPath(Stack<SimNode*> networkPath)
    {
        sourceRoute = networkPath;
    }


}
