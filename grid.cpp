#include "grid.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#define EMPTYSPACE -1


namespace EIN_JRW_Prog5
{

    //Author Erik Nadel (einadel@wpi.edu)
    Grid::Grid()
    {
        idGrid = NULL;
        xLength = 0;
        yLength = 0;
    }
    //Author Erik Nadel (einadel@wpi.edu)
    Grid::Grid(int xDim, int yDim)
    {
        // Initialize 2d array
        idGrid = new int*[xDim];
        for (int i = 0 ; i < xDim ; i++)
            idGrid[i] = new int[yDim];

        xLength = xDim;
        yLength = yDim;


        // fill grid with empty spaces
        for(int x = 0; x < xLength; ++x)
        {
            for(int y = 0; y < yLength; ++y)
            {
                idGrid[x][y] = EMPTYSPACE;
            }
        }
    }
    //Author Erik Nadel (einadel@wpi.edu)
    // Move a router based on its direction
    void Grid::moveRouter(Router* r)
    {
        //printf("toMove x: d toMove y: %d \n", toMove->posX, toMove->posY);
        location current = r->getLocation();
        // Determine how the move method will be called.
        switch(r->getDirection())
        {
            case NORTH:
                moveObject(current, location( current.GetxCoord()-1,current.GetyCoord()), r);
                break;
            case EAST:
                moveObject(current,location(current.GetxCoord(),current.GetyCoord()+1),r);
                break;
            case SOUTH:
                moveObject(current,location(current.GetxCoord()+1,current.GetyCoord()),r);
                break;
            case WEST:
                moveObject(current,location(current.GetxCoord(),current.GetyCoord()-1),r);
                break;
        }

    }

    //Author Erik Nadel (einadel@wpi.edu)
    // Helper method for moveRouter
    void Grid::moveObject(location cur, location next, Router *r)
    {
        // Handle a router trying to bounce on a wall.
        if(this->isOnEdge(next))
        {
            int fixedX = next.GetxCoord();
            int fixedY = next.GetyCoord();
            // Fix the coordinates of the place to land depending on where router tried to move.
            if(next.GetxCoord() < 0) // Upper boundary reverses the router's direction to SOUTH for example.
            {
                fixedX = 1;
                r->setDirection(SOUTH);

            }
            if(next.GetxCoord() >= this->xLength) // Lower boundary
            {
                fixedX = xLength - 2;
                r->setDirection(NORTH);
            }
            if(next.GetyCoord() < 0) // Left  wall
            {
                fixedY = 1;
                r->setDirection(EAST);
            }
            if(next.GetyCoord() >= this->yLength) // Right wall
            {
                fixedY = yLength - 2;
                r->setDirection(WEST);
            }
            // Call move again with corrected coordinates

            location fixed(fixedX,fixedY);

            moveObject(cur,fixed,r);
        }

        // emptyspaces are immediately replaced.
        else if(!isOccupied(next))
        {
            // Replace the space with the router moving.
            int temp = idGrid[cur.GetxCoord()][cur.GetyCoord()];
            idGrid[next.GetxCoord()][next.GetyCoord()] = temp;
            idGrid[cur.GetxCoord()][cur.GetyCoord()] = EMPTYSPACE;
            // Update the routers's current position.
            r->setLocation(next);
            //printf("Moved %d\n", p->playerNum);
            return;
        }
        // handle a router space
        else if(isOccupied(next))
        {
            // Bounce off of the router
            // Don't bounce off of self. (This would happen at a wall bounce)
            if(idGrid[next.GetxCoord()][next.GetyCoord()] == r->getID())
                return;
            // Bounce according to direction
            switch (r->getDirection())
            {
            case NORTH:
                moveObject(cur,location(next.GetxCoord()-1,next.GetyCoord()),r);
                break;
            case EAST:
                moveObject(cur,location(next.GetxCoord(),next.GetyCoord()+1),r);
                break;
            case SOUTH:
                moveObject(cur,location(next.GetxCoord()+1,next.GetyCoord()),r);
                break;
            case WEST:
                moveObject(cur,location(next.GetxCoord(),next.GetyCoord()-1),r);
                break;
            }
        }
    }

    //Author Erik Nadel (einadel@wpi.edu)
    bool Grid::isOnEdge(location l)
    {
        // Cover X boundaries
        if(l.GetxCoord() < 0 || l.GetxCoord() >= xLength)
            return true;
        // Y Boundaries
        if(l.GetyCoord() < 0 || l.GetyCoord() >= yLength)
            return true;
        // Otherwise its not out of bounds
        else
            return false;
    }

    //Author Erik Nadel (einadel@wpi.edu)
    // Is the location occupied??
    bool Grid::isOccupied(location l)
    {
        return idGrid[l.GetxCoord()][l.GetyCoord()] != EMPTYSPACE;
    }

    //Author Erik Nadel (einadel@wpi.edu)
    // Print the grid
    void Grid::print()
    {
        for(int x = 0; x < xLength; ++x)
        {
            for(int y = 0; y < yLength; ++y)
            {
                if(idGrid[x][y] == EMPTYSPACE)
                    std::cout << " - ";
                else
                    std::cout << std::setw(2) << idGrid[x][y] << " ";
            }
            std::cout << std::endl;
        }
    }
// Author Jacob Watson (jrwatson@wpi.edu)
    // Add a node to the grid
    void Grid::addObject(SimNode *r)
    {
        bool placed = false;

        // Keep trying to place until a spot has been found
        while(!placed)
        {
            int x = rand() % xLength;
            int y = rand() % yLength;
            location potential(x,y);
            if(!isOccupied(potential))
            {
                idGrid[x][y] = r->getID();
                r->setLocation(potential);
                placed = true;
            }
        }
    }
// Author Jacob Watson (jrwatson@wpi.edu)
    // How long is the grid? for receiver calc time purposes
    int Grid::getYLength()
    {
        return yLength;
    }
// Author Jacob Watson (jrwatson@wpi.edu)
    // Print center grid between left and right grid
    void Grid::printBetween(Grid left, Grid center, Grid right)
    {
        // Their height needs to be the same
        assert(left.xLength == center.xLength && center.xLength == right.xLength);

        for(int x = 0; x < center.xLength; x++)
        {
            // Traverse through the row of every grid and print what is there
            for(int y = 0; y < left.yLength; ++y)
            {
                if(left.idGrid[x][y] != EMPTYSPACE)
                    std::cout << std::setw(2) << left.idGrid[x][y] << " ";
                else
                    std::cout << " - ";
            }

            std::cout << "|"; // Seperator

            for(int y = 0; y < center.yLength; ++y)
            {
                if(center.idGrid[x][y] != EMPTYSPACE)
                    std::cout << std::setw(2) << center.idGrid[x][y] << " ";
                else
                    std::cout << " - ";
            }

            std::cout << "|"; // Seperator

            for(int y = 0; y < right.yLength; ++y)
            {
                if(right.idGrid[x][y] != EMPTYSPACE)
                    std::cout << std::setw(2) << right.idGrid[x][y] << " ";
                else
                    std::cout << " - ";
            }
            std::cout << std::endl;
        }
    }

}
