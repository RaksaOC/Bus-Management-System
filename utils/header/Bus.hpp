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

    int getSeatLeft() { return this->seatLeft; };
    vector<int> getWantedSeatNums() { return this->wantedSeatNums; };
    vector<int> getSeatNumChanges() { return this->seatNumsChanged; };

    void showSeatLayoutBlank();
};

void Bus::printBusInfo()
{
    cout << "\n\n\t\t\t\tCHOSEN BUS INFO\n\n";
    cout << "\033[33m******************************************* \033[0m" << endl;
    cout << "\033[33m* \033[0m Bus ID: " << busID << endl;
    cout << "\033[33m* \033[0m Bus Type: " << busType << endl;
    cout << "\033[33m* \033[0m Departure Time: " << dpTime << endl;
    cout << "\033[33m* \033[0m From: " << this->route["from"] << endl;
    cout << "\033[33m* \033[0m To: " << this->route["to"] << endl;
    cout << "\033[33m* \033[0m Seat Capacity: " << seatCap << endl;
    cout << "\033[33m* \033[0m Seats Left: " << seatLeft << endl;
    cout << "\033[33m* \033[0m Seat Price: " << seatPrice << endl;
    cout << "\033[33m******************************************* \033[0m" << endl;
    cout << "\n\n";
}

void Bus::showSeatLayout()
{
    string avail = "available";
    for (const auto &seat : seats)
    {
        int seatNum = seat["seatNum"];
        if (seat["status"] == avail)
        {
            cout << "\033[36m[ \033[0m " << seatNum << " \033[36m] \033[0m";
        }
        else
        {
            cout << "\033[31m[ X ] \033[0m";
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
        cout << "\033[36m[ \033[0m " << seatNum << " \033[36m] \033[0m";

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
        cout << "\033[36mSelect a seat \033[0m\n> ";
        cin >> seatNum;
        if (isSeatAvailable(seatNum))
        {
            break;
        }
        else
        {
            cout << seatUnavailableMessage;
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
        cout << "\033[36mEnter the number of seats to book \033[0m\n> ";
        cin >> numberOfSeatToBook;
        if (numberOfSeatToBook <= seatLeft && !(numberOfSeatToBook < 2))
        {
            break;
        }
        else
        {
            cout << invalidInputMessage;
        }
    }
    for (int i = 0; i < numberOfSeatToBook; i++)
    {
        while (1)
        {
            cout << "\033[36mSeat \033[0m " << i + 1 << ": ";
            cin >> seatNum;
            if (isSeatAvailable(seatNum))
            {
                seatNumberArr.push_back(seatNum);
                break;
            }
            else
            {
                cout << "\033[31mSeat Unavailable \033[0m\n";
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

        refundTypeMenu();
        cout << "\033[36m1. \033[0m Refund specific seats\n";
        cout << "\033[36m2. \033[0m Refund all seats\n> ";
        cin >> refundType;
        if (!(refundType < 1 || refundType > 2))
        {
            break;
        }
        else
        {
            cout << invalidInputMessage;
        }
    }

    if (refundType == 1)
    {
        while (1)
        {
            cout << "\033[36mEnter the number of seats to refund \033[0m\n> ";
            cin >> numOfSeatsToRefund;
            if (numOfSeatsToRefund > seatNumsToRefund.size() || numOfSeatsToRefund <= 0)
            {
                cout << invalidInputMessage;
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
                cout << "\033[36mSeat: \033[0m ";
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