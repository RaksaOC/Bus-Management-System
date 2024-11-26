#ifndef Route_hpp
#define Route_hpp

#include <iostream>
#include <vector>

using namespace std;

class Route
{
private:
    string origin;        // Starting point of the route
    string destination;   // End point of the route
    vector<string> stops; // Intermediate stops (optional for future)
    string schedule;      // Schedule for the route (e.g., departure time)
public:
    // Constructor
    Route(string origin, string destination);

    // Core Route Methods
    void setRoute(string origin, string destination); // Sets the origin and destination
    void addStop(string stop);                        // Adds a stop to the route
    void setSchedule(string time);                    // Sets the schedule for the route
    void displayRouteDetails();                       // Displays route information
};

// Constructor
Route::Route(string origin, string destination)
{
    this->origin = origin;
    this->destination = destination;
    // [TO DO] Initialize other attributes if necessary
}

// Sets the origin and destination
void Route::setRoute(string origin, string destination)
{
    this->origin = origin;
    this->destination = destination;
    // [TO DO] Update and save route data to file if needed
}

// Adds a stop to the route
void Route::addStop(string stop)
{
    // [TO DO]
    // - Add `stop` to the `stops` vector
    // - Ensure no duplicates if required
}

// Sets the schedule for the route
void Route::setSchedule(string time)
{
    schedule = time;
    // [TO DO]
    // - Validate and format the schedule string if needed
}

// Displays route information
void Route::displayRouteDetails()
{
    // [TO DO]
    // - Print the origin, destination, stops, and schedule
    // - Format the output for readability
}

#endif
