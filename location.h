#ifndef LOCATION_H
#define LOCATION_H

namespace EIN_JRW_Prog5
{

enum Direction{ NORTH, SOUTH, EAST, WEST };

class location
{
    public:
        location();
        location(int x, int y);
        int GetxCoord() { return xCoord; }
        void SetxCoord(int val) { xCoord = val; }
        int GetyCoord() { return yCoord; }
        void SetyCoord(int val) { yCoord = val; }
    private:
        int xCoord;
        int yCoord;
};
}
#endif // LOCATION_H
