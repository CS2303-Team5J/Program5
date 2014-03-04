#include "location.h"


namespace EIN_JRW_Prog5{

// Default constructor
location::location()
{

}

// Author Jacob Watson (jrwatson@wpi.edu)
// Constructor
location::location(int x, int y)
{
    this->SetxCoord(x);
    this->SetyCoord(y);
}
}
