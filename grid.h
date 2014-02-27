#ifndef GRID_H
#define GRID_H
#include "location.h"
#include "router.h"
namespace EIN_JRW_Prog5
{
    class Grid
    {
        public:
            Grid();
            Grid(int xDim, int yDim);
            void addRouter(Router* r);
            void moveRouter(Router* r);
            void print();
        private:
            void moveObject(location cur, location next, Router* r);
            bool isOnEdge(location l);
            bool isOccupied(location l);

            int xLength;
            int yLength;

            int **idGrid;

    };
}
#endif
