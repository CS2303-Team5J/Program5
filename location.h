#ifndef LOCATION_H
#define LOCATION_H

namespace EIN_JRW_Prog5
{

// Directions 0,1,2,3
enum Direction{ NORTH, SOUTH, EAST, WEST };

class location
{
    public:
        location(); // Default constructor
        location(int x, int y); // Constructor

        // Author Erik Nadel (einadel@wpi.edu)
        int GetxCoord() { return xCoord; } // Get X coordinate

        // Author Erik Nadel (einadel@wpi.edu)
        void SetxCoord(int val) { xCoord = val; } // Set x coordinate

        // Author Erik Nadel (einadel@wpi.edu)
        int GetyCoord() { return yCoord; } // Get y coordinate

        // Author Erik Nadel (einadel@wpi.edu)
        void SetyCoord(int val) { yCoord = val; } // Set y coordinate
    private:
        int xCoord;
        int yCoord;
};
}
#endif // LOCATION_H
