#ifndef Bus_hpp
#define Bus_hpp

#include <iostream>
#include <cstdlib>
#include <vector>
#include "../libs/json.hpp"
#include "Route.hpp"
#include "menu.hpp"

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
    vector<int> seatNumsChanged;
    vector<int> wantedSeatNums;

public:
    Bus();
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

    // For Reservation
    void printBusInfo();
    void showSeatLayout(); // Displays seat layout of the bus
    json reserveSeat();    // Reserves a single seat
    json reserveSeats();   // Reserves multiple seats

    // For Refund
    json refundSeat(vector<int> seatNumsToRefund);
    json refundSeats(vector<int> seatNumsToRefund);
    void setSeatLeft(int s) { this->seatLeft = s; }

    int getSeatLeft() { return this->seatLeft; };
    vector<int> getWantedSeatNums() { return this->wantedSeatNums; };
    vector<int> getSeatNumChanges() { return this->seatNumsChanged; };

    void showSeatLayoutBlank();
};

void Bus::printBusInfo()
{
    cout << "\n\n\t\t\t\tCHOSEN BUS INFO\n\n";
    cout << "*******************************************" << endl;
    cout << "* Bus ID: " << busID << endl;
    cout << "* Bus Type: " << busType << endl;
    cout << "* Departure Time: " << dpTime << endl;
    cout << "* From: " << this->route["from"] << endl;
    cout << "* To: " << this->route["to"] << endl;
    cout << "* Seat Capacity: " << seatCap << endl;
    cout << "* Seats Left: " << seatLeft << endl;
    cout << "* Seat Price: " << seatPrice << endl;
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

void Bus::showSeatLayoutBlank()
{
    for (const auto &seat : seats)
    {
        int seatNum = seat["seatNum"];
        cout << "[ " << seatNum << " ]";

        if (seatNum % 2 == 0)
        {
            cout << "\t";
        }
        if (seatNum % 4 == 0)
        {
            cout << "\n";
        }
    }
    cout << "\n";
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
    int numberOfSeatToBook;
    while (1)
    {
        cout << "Enter the number of seats to book\n> ";
        cin >> numberOfSeatToBook;
        if (numberOfSeatToBook <= seatLeft && !(numberOfSeatToBook < 2))
        {
            break;
        }
        else
        {
            cout << "Error: Invalid Input\n";
        }
    }
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
    this->seatNumsChanged = seatNumberArr;
    this->seatLeft = this->seatLeft - numberOfSeatToBook;
    return seats;
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

json Bus::refundSeat(vector<int> seatNumsToRefund)
{
    int seatToRefund = seatNumsToRefund.at(0);
    for (auto &seat : seats)
    {
        if (seat["seatNum"] == seatToRefund)
        {
            seat["status"] = "available";
            seatNumsChanged.push_back(seat["seatNum"]);
            break;
        }
    }
    return seats;
}

json Bus::refundSeats(vector<int> seatNumsToRefund)
{
    vector<int> wantedSeatNumbers;
    int numOfSeatsToRefund;
    int seatNum;
    bool isSeatNumExist = false;
    int refundType;
    while (1)
    {

        cout << "\n\n\t\tREFUND TYPE\n\n";
        cout << "1. Refund specific seats\n";
        cout << "2. Refund all seats\n> ";
        cin >> refundType;
        if (!(refundType < 1 || refundType > 2))
        {
            break;
        }
        else
        {
            cout << "Error: Invalid Input";
        }
    }

    if (refundType == 1)
    {
        while (1)
        {
            cout << "Enter the number of seats to refund\n> ";
            cin >> numOfSeatsToRefund;
            if (numOfSeatsToRefund > seatNumsToRefund.size() || numOfSeatsToRefund <= 0)
            {
                cout << "Error: Invalid Input";
            }
            else
            {
                break;
            }
        }

        for (int i = 0; i < numOfSeatsToRefund; i++)
        {
            while (1)
            {
                cout << "Seat: ";
                cin >> seatNum;
                isSeatNumExist = false;
                for (int i = 0; i < seatNumsToRefund.size(); i++)
                {
                    if (seatNumsToRefund[i] == seatNum)
                    {
                        isSeatNumExist = true;
                        break;
                    }
                }
                if (isSeatNumExist)
                {
                    break;
                }
                else
                {
                    cout << invalidInputMessage;
                }
            }
            wantedSeatNumbers.push_back(seatNum);
        }
        this->wantedSeatNums = wantedSeatNumbers;
        seatNumsChanged = seatNumsToRefund;
        for (int i = seatNumsChanged.size() - 1; i >= 0; --i) // Iterate backwards
        {
            for (int j = 0; j < wantedSeatNumbers.size(); ++j)
            {
                if (seatNumsChanged[i] == wantedSeatNumbers[j])
                {
                    seatNumsChanged.erase(seatNumsChanged.begin() + i); // Erase safely
                    break;                                              // Exit inner loop to prevent further comparisons
                }
            }
        }
        int i = 0;
        for (auto &seat : seats)
        {
            if (i < wantedSeatNumbers.size() && (seat["seatNum"] == wantedSeatNumbers.at(i)))
            {
                seat["status"] = "available";
                i++;
            }
            if (i >= wantedSeatNumbers.size())
            {
                this->seatLeft += wantedSeatNumbers.size();

                return seats;
            }
        }
    }
    else
    {
        int i = 0;
        for (auto &seat : seats)
        {
            cout << i << " ";
            if (i < seatNumsToRefund.size() && (seat["seatNum"] == seatNumsToRefund.at(i)))
            {
                seat["status"] = "available";
                i++;
            }
            if (i >= seatNumsToRefund.size())
            {
                seatNumsChanged.push_back(-1);
                this->seatLeft += seatNumsToRefund.size();
                break;
            }
        }
        return seats;
    }
    return seats;
}

#endif