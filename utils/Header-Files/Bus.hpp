#ifndef Bus_hpp
#define Bus_hpp

// -------------------------------------------------------

#include "User.hpp"

#include <iostream>
#include <vector>
using namespace std;

class Bus
{
private:
    string busID;
    string busType;
    int seatCap;
    vector <int> seatStatus;
public:
    Bus();
};



#endif
