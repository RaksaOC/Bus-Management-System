#ifndef Bus_hpp
#define Bus_hpp

#include <iostream>
#include <vector>
#include "Route.hpp"

using namespace std;

class Bus
{
private:
    string busID;           // Unique ID for the bus
    string busType;         // Type of bus (e.g., luxury, economy)
    int seatCap;            // Total seat capacity
    int seatPrice;          // Price per seat
    vector<int> seatStatus; // Seat status (e.g., 0 = available, 1 = reserved)
public:
    // Constructor
    Bus(string ID, string type, int cap, int price);

    // Core Bus Methods
    void showSeatLayout();                            // Displays seat layout of the bus
    bool reserveSeat(int seat);                       // Reserves a single seat
    bool reserveSeats(vector<int> seats);             // Reserves multiple seats
    bool isSeatAvailable(int seat);                   // Checks if a specific seat is available
    void setRoute(string origin, string destination); // Sets a route for the bus
};

Bus::Bus(string ID, string type, int cap, int price)
{
    busID = ID;
    busType = type;
    seatCap = cap;
    seatPrice = price;
    seatStatus = vector<int>(cap, 0); // Initialize all seats as available
    // [TO DO] Load additional bus data if needed
}


void Bus::showSeatLayout()
{
    // [TO DO]
    // - Iterate through `seatStatus` vector
    // - Display seat numbers and their availability (e.g., 0 = available, 1 = reserved)
}

// Reserves a single seat
bool Bus::reserveSeat(int seat)
{
    // [TO DO]
    // - Check if the seat number is valid and available
    // - If available, mark it as reserved (1) and return true
    // - If not, return false
}

// Reserves multiple seats
bool Bus::reserveSeats(vector<int> seats)
{
    // [TO DO]
    // - Iterate through the provided `seats` vector
    // - For each seat, check availability using `isSeatAvailable`
    // - Reserve seats if all are available; otherwise, return false
}

// Checks if a specific seat is available
bool Bus::isSeatAvailable(int seat)
{
    // [TO DO]
    // - Verify if `seat` index is within bounds of `seatStatus`
    // - Return true if `seatStatus[seat] == 0` (available), otherwise false
}

// Sets a route for the bus
void Bus::setRoute(string origin, string destination)
{
    Route route(origin, destination); // Create a new Route object
    // [TO DO]
    // - Save or update the route information for this bus
    // - Write changes to file if persistent storage is needed
}

#endif
