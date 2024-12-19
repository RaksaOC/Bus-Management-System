#ifndef Bus_hpp
#define Bus_hpp

#include <iostream>
#include <cstdlib>
#include <vector>
#include "../libs/json.hpp"
#include "Route.hpp"

using json = nlohmann::json;

using namespace std;

class Bus
{
private:
    // Attributes
    string busType; // Type of bus (e.g., luxury, economy)
    string dpTime;  // departure time
    string busID;   // Unique ID for the bus
    json route;     // route of bus
    int seatCap;    // Total seat capacity
    int seatLeft;   // remaining seats
    int seatPrice;  // Price per seat
    json seats;

    bool isSeatAvailable(int seat); // Checks if a specific seat is available
    vector<int> numOfSeatsChanged;

public:
    // Constructor
    Bus(string type, string dpTime, string id, json route, int cap, int rem, int price, json seats)
    {
        busType = type;
        this->dpTime = dpTime;
        busID = id;
        this->route = route;
        seatCap = cap;
        seatLeft = rem;
        seatPrice = price;
        this->seats = seats;
    };

    // Core Bus Methods
    json refundAllSeat(vector <int>);
    void printHistory(vector <string>);
    void printBusInfo();
    void showSeatLayout(); // Displays seat layout of the bus
    json singleRefund(vector <int>);
    json bulkRefund(vector <int>);
    json reserveSeat();    // Reserves a single seat
    json reserveSeats();   // Reserves multiple seats
    int getSeatLeft() { return this->seatLeft; };
    vector<int> getSeatNumChanges() { return this->numOfSeatsChanged; };
};

json Bus::bulkRefund(vector <int> seatNum){
    int choice;
    cout<<"1. Refund all seats\n2. Refund one seat\n> ";
    cin>>choice;
    json seatsToChange;
    switch(choice){
        case 1:
            seatsToChange= refundAllSeat(seatNum);
            break;
        case 2:
        //fuck you
            break;
    }
    return seatsToChange;
}
json Bus::refundAllSeat(vector <int> seatNum){
    int i=0;
    for(auto & seat: seats){
        if(seat["seatNum"]==seatNum.at(i)){
            seat["status"]=="available";
            i++;
        }
    }
    return seats;
}

void Bus::printBusInfo()

{
    cout << "\n\n\t\t\t\tCHOSEN BUS INFO\n\n";
    cout << "*******************************************" << endl;
    cout << "Bus ID: " << busID << endl;
    cout << "Bus Type: " << busType << endl;
    cout << "Departure Time: " << dpTime << endl;
    cout << "From: " << this->route["from"] << endl;
    cout << "To: " << this->route["to"] << endl;
    cout << "Seat Capacity: " << seatCap << endl;
    cout << "Seats Left: " << seatLeft << endl;
    cout << "Seat Price: " << seatPrice << endl;
    cout << "*******************************************" << endl;
    cout << "\n\n";
}

void Bus::showSeatLayout()
{
    string avail = "available";
    cout << "\n\n\t\t\t\tSEAT SELECTION\n\n";
    for (const auto &seat : seats)
    {
        int seatNum = seat["seatNum"];
        if (seat["status"] == avail)
        {
            cout << "[ " << seatNum << " ]";
        }
        else
        {
            cout << "[ X ]";
        }
        if (seatNum % 2 == 0)
        {
            cout << "\t";
        }
        if (seatNum % 4 == 0)
        {
            cout << "\n";
        }
    }
    cout << "\n\n";
}

// Reserves a single seat
json Bus::reserveSeat()
{
    int seatNum;
    while (1)
    {
        cout << "Select a seat\n> ";
        cin >> seatNum;
        if (isSeatAvailable(seatNum))
        {
            break;
        }
        else
        {
            cout << "Error: Seat unavailable\n";
        }
    }

    json seatToReturn;
    for (auto &seat : seats)
    {
        if (seat["seatNum"] == seatNum)
        {
            seat["status"] = "reserved";
            seatToReturn = seat;
            break;
        }
    }

    return seatToReturn;
}
// Reserves multiple seats
json Bus::reserveSeats()
{
    vector<int> seatNumberArr;
    vector<json> seatsArr;
    int seatNum;
    cout << "Enter the number of seats to book\n> ";
    int numberOfSeatToBook;
    cin >> numberOfSeatToBook;
    for (int i = 0; i < numberOfSeatToBook; i++)
    {
        while (1)
        {
            cout << "Seat: " << i + 1 << ": ";
            cin >> seatNum;
            if (isSeatAvailable(seatNum))
            {
                seatNumberArr.push_back(seatNum);
                break;
            }
            else
            {
                cout << "Seat Unavailable\n";
            }
        }
    }
    int i = 0;
    for (auto &seat : seats)
    {
        if ((i < seatNumberArr.size()) && (seat["seatNum"] == seatNumberArr.at(i)))
        {
            seat["status"] = "reserved";
            i++;
        }
        if (i >= seatNumberArr.size())
        {
            break;
        }
    }
    this->numOfSeatsChanged = seatNumberArr;
    this->seatLeft = this->seatLeft - numberOfSeatToBook;
    return seats;

    // [TO DO]
    // - Prompt the user to input number of seats to book
    // - Let user input their seat numbers
    // - Error handle
    // - Return back a vector of seats(json obj) or vector of seatNumbers(user class will handle the file writing)
}

// Checks if a specific seat is available
bool Bus::isSeatAvailable(int seatNum)
{
    for (const auto &seat : seats)
    {
        if (seat["seatNum"] == seatNum && seat["status"] == "available")
        {
            return true;
        }
    }
    return false;
}

#endif