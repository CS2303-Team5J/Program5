#ifndef SENDERSTATS_H
#define SENDERSTATS_H
#include <vector>


namespace EIN_JRW_Prog5
{
    // Each senderstats represents a host. The receiver makes a sender stats object for each host that it got packets from.
    class SenderStats
    {
        public:
        // Constructor
        // Author Erik Nadel (einadel@wpi.edu)
        SenderStats(int senderID) {this->senderID = senderID; numPacketsFrom = 0; totalResponseTime = 0; varianceSum = 0;}
        // Modification methods
            // Increment the number of packets from a host
            // Author Erik Nadel (einadel@wpi.edu)
        void addPacket(int responseTime) { totalResponseTime+= responseTime; numPacketsFrom++; responseTimes.push_back(responseTime);}

        // Author Erik Nadel (einadel@wpi.edu)
        // Non-modification methods
            // Get the average response time of packets from the host
        double getAvgResponseTime() {return totalResponseTime / (double) numPacketsFrom;}

        // Author Erik Nadel (einadel@wpi.edu)
            // Get the ID that the senderstats is relating to
        int getStatSenderID() {return this->senderID;}

        // Author Erik Nadel (einadel@wpi.edu)
            // Get the number of packets from the given host (based on counted stats)
        int getNumPackets() {return numPacketsFrom;}

        // Author Jacob Watson (jrwatson@wpi.edu)
        double calculateVariance()
        {
            for(size_t x = 0; x <responseTimes.size(); ++x)
            {
                varianceSum +=  (double) (getAvgResponseTime() - (double)responseTimes[x]) * (double) (getAvgResponseTime() - (double)responseTimes[x]);
            }
            return varianceSum / responseTimes.size();
        }

        private:

        int senderID;
        int numPacketsFrom;
        int totalResponseTime;
        std::vector<int> responseTimes;
        int varianceSum;
    };
}

#endif
