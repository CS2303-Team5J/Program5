// Author Erik Nadel (einadel@wpi.edu) (entire file)

#ifndef GRID_H
#define GRID_H
#include "location.h"
#include "router.h"
//#include "simnode.h"

namespace EIN_JRW_Prog5
{
    class Router;
    class SimNode;

    // Grid system for the simnodes
    class Grid
    {
        public:
            // Constructors
            Grid();
            Grid(int xDim, int yDim);

            // Add an object to the grid
            void addObject(SimNode* r);
            // Move a router based on its direction
            void moveRouter(Router* r);

            // Print the grid alone
            void print();
            // Get the length of the grid
            int getYLength();
            // Print a grid between two grids
            void printBetween(Grid left, Grid center, Grid right);
        private:
            // helper method for moving a router
            void moveObject(location cur, location next, Router* r);
            // Is the location on an edge?
            bool isOnEdge(location l);
            // Is the location occupied?
            bool isOccupied(location l);

            int xLength;
            int yLength;

            int **idGrid;

    };
}
#endif
