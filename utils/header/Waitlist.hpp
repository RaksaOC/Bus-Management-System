#ifndef Wait_hpp
#define Wait_hpp

#include <iostream>
#include <vector>
#include <limits>
#include <stack>
#include <ctime>
#include "Bus.hpp"
#include "menu.hpp"
#include "validation.hpp"

#define dataFilePath "../utils/database/Data.json"

using json = nlohmann::json;
using namespace std;

class Waitlist
{
private:
    string busID;
    vector<int> seatNumbers;
    string userID;
    int waitListBookingType;

    void loadData();

    // helper functions for add to waitlist
    void addToWaitlistSingle();
    void addToWaitlistBulk();

    void generateWaitlistObj(int, int, vector<int>, int);
    void generateReservationFromWaitlist(string, string, vector<int>);
    void storeDataWaitList();

    json data;
    json buses;
    json waitList;
    json reservations;
    json users;
    json busToModify;

public:
    Waitlist() {};
    int choiceToEnterWaitlist();
    void addToWaitlist(string, string);
    bool processWaitlistSingle(string busID, int seatsRefunded);
    bool processWaitlistBulk(string busID, vector<int> seatsRefunded);
};

void Waitlist::loadData()
{
    ifstream readData(dataFilePath);
    readData >> data;
    buses = data["buses"];
    waitList = data["waitList"];
    users = data["users"];
    reservations = data["reservations"];
}

int Waitlist::choiceToEnterWaitlist()
{
    int choice;
    while (1)
    {
        cout << "\nWould you like to enter the waitlist for this bus?\n1. Yes\n2. No\n\n> ";
        cin >> choice;
        if (choice < 1 || choice > 2)
        {
            cout << invalidInputMessage;
        }
        else
        {
            break;
        }
    }
    return choice;
}

void Waitlist::addToWaitlist(string uID, string bID)
{
    loadData();
    for (auto &bus : buses)
    {
        if (bus["id"] == bID)
        {
            busToModify = bus;
            break;
        }
    }
    this->userID = uID;
    this->busID = bID;

    int choice;
    while (1)
    {
        cout << "Enter booking type\n1. Single\n 2. Bulk (Coming Soon)\n\n> ";
        cin >> choice;
        if (choice != 1) // to change to include bulk reservaiton
        {
            cout << invalidInputMessage;
        }
        else
        {
            break;
        }
    }
    if (choice == 1)
    {
        addToWaitlistSingle();
    }
    // else
    // {
    //     addToWaitlistBulk();
    // }
}

void Waitlist::addToWaitlistSingle()
{
    int seatNum;
    int waitType;
    cout << "\nWould you like to waitlist for a specific seat or any?" << endl;
    cout << "1. Specific\n";
    cout << "2. Any Seat\n\n> ";
    cin >> waitType;
    if (waitType == 1)
    {
        while (1)
        {
            cout << "Enter seat Number\n\n> ";
            cin >> seatNum;
            cout << "The cap of bus is : " << busToModify["seatCap"] << endl;
            if (seatNum <= busToModify["seatCap"] && seatNum > 0)
            {
                break;
            }
            else
            {
                cout << invalidInputMessage;
            }
        }
        vector<int> seatNums;
        seatNums.push_back(seatNum);
        generateWaitlistObj(1, 1, seatNums, 1);
    }
    else
    {
        cout << "You have been added to the waitlist\n";
        vector<int> empty;
        generateWaitlistObj(1, 2, empty, 1);
    }
}

void Waitlist::addToWaitlistBulk()
{
    // [FOR FUTURE]
    vector<int> seatNums;
    int seatNum;
    int numOfSeatsToBook;
    int waitType;
    cout << "\nWould you like to waitlist for a specific seat or any?" << endl;
    cout << "1. Specific\n";
    cout << "2. Any Seat\n\n> ";
    cin >> waitType;
    if (waitType == 1)
    {
        while (1)
        {
            cout << "Enter the number of seats to book\n\n> ";
            cin >> numOfSeatsToBook;
            if (numOfSeatsToBook < 2 || numOfSeatsToBook > busToModify["seatCap"])
            {
                cout << invalidInputMessage;
            }
            else if (numOfSeatsToBook <= busToModify["seatCap"])
            {
                break;
            }
        }
        for (int i = 0; i < numOfSeatsToBook; i++)
        {
            while (1)
            {
                cout << "Seat " << i + 1 << ": ";
                cin >> seatNum;
                if (seatNum > 0 && seatNum <= busToModify["seatCap"])
                {
                    seatNums.push_back(seatNum);
                    break;
                }
                else
                {
                    cout << invalidInputMessage;
                }
            }
        }
        generateWaitlistObj(2, 1, seatNums, seatNums.size());
    }
    else
    {
        int numOfSeatsToWaitlist;
        cout << "Enter the number of seats to reserve for\n\n> ";
        cin >> numOfSeatsToWaitlist;
        vector<int> empty;
        generateWaitlistObj(2, 2, empty, numOfSeatsToWaitlist);
    }
}

void Waitlist::generateWaitlistObj(int bType, int wType, vector<int> seatNums, int numOfSeatsToWaitlist)
{
    if (bType == 1 && wType == 1) // single and specific
    {
        json sW;
        string baseID = "W000000";
        int lastID = sW.size();
        string lastID_string = to_string(lastID);
        int start = baseID.size() - lastID_string.size();
        int j = 0;
        for (int i = start; i < baseID.size(); i++)
        {
            baseID[i] = lastID_string[j];
            j++;
        }
        time_t currentTime = time(nullptr);
        string time = ctime(&currentTime); // Convert to string
        time.pop_back();
        json newWaitObj;
        newWaitObj["id"] = baseID;
        newWaitObj["waitType"] = "specific";
        newWaitObj["userID"] = userID;
        newWaitObj["busID"] = busID;
        newWaitObj["size"] = 1;
        newWaitObj["seatNumber"] = seatNums.at(0);
        newWaitObj["time"] = time;
        newWaitObj["status"] = "active";
        waitList["singleWaitList"].push_back(newWaitObj);
    }
    else if (bType == 1 && wType == 2) // single and any
    {
        json sW;
        string baseID = "W000000";
        int lastID = sW.size();
        string lastID_string = to_string(lastID);
        int start = baseID.size() - lastID_string.size();
        int j = 0;
        for (int i = start; i < baseID.size(); i++)
        {
            baseID[i] = lastID_string[j];
            j++;
        }
        time_t currentTime = time(nullptr);
        string time = ctime(&currentTime); // Convert to string
        time.pop_back();
        json newWaitObj;
        newWaitObj["id"] = baseID;
        newWaitObj["waitType"] = "any";
        newWaitObj["userID"] = userID;
        newWaitObj["busID"] = busID;
        newWaitObj["size"] = 1;
        newWaitObj["seatNumber"] = nullptr;
        newWaitObj["time"] = time;
        newWaitObj["status"] = "active";
        waitList["singleWaitList"].push_back(newWaitObj);
    }
    // else if (bType == 2 && wType == 1) // bulk and specific
    // {
    //     json bW;
    //     string baseID = "WB000000";
    //     int lastID = bW.size();
    //     string lastID_string = to_string(lastID);
    //     int start = baseID.size() - lastID_string.size();
    //     int j = 0;
    //     for (int i = start; i < baseID.size(); i++)
    //     {
    //         baseID[i] = lastID_string[j];
    //         j++;
    //     }
    //     time_t currentTime = time(nullptr);
    //     string time = ctime(&currentTime); // Convert to string
    //     time.pop_back();
    //     json newWaitObj;
    //     newWaitObj["id"] = baseID;
    //     newWaitObj["waitType"] = "specific";
    //     newWaitObj["userID"] = userID;
    //     newWaitObj["busID"] = busID;
    //     newWaitObj["size"] = numOfSeatsToWaitlist;
    //     newWaitObj["seatNumber"] = seatNums;
    //     newWaitObj["time"] = time;
    //     newWaitObj["status"] = "active";
    //     waitList["bulkWaitList"].push_back(newWaitObj);
    // }
    // else // bulk and any
    // {
    //     json bW;
    //     string baseID = "WB000000";
    //     int lastID = bW.size();
    //     string lastID_string = to_string(lastID);
    //     int start = baseID.size() - lastID_string.size();
    //     int j = 0;
    //     for (int i = start; i < baseID.size(); i++)
    //     {
    //         baseID[i] = lastID_string[j];
    //         j++;
    //     }
    //     time_t currentTime = time(nullptr);
    //     string time = ctime(&currentTime); // Convert to string
    //     time.pop_back();
    //     json newWaitObj;
    //     newWaitObj["id"] = baseID;
    //     newWaitObj["waitType"] = "any";
    //     newWaitObj["userID"] = userID;
    //     newWaitObj["busID"] = busID;
    //     newWaitObj["size"] = numOfSeatsToWaitlist;
    //     newWaitObj["seatNumber"] = nullptr;
    //     newWaitObj["time"] = time;
    //     newWaitObj["status"] = "active";
    //     waitList["bulkWaitList"].push_back(newWaitObj);
    // }
    storeDataWaitList();
}

void Waitlist::storeDataWaitList()
{
    ofstream storeData(dataFilePath);
    if (!storeData.is_open())
    {
        cerr << openFileFailMessage;
        cerr << dataFilePath;
        return;
    }
    data["reservations"] = reservations;
    data["users"] = users;
    data["waitList"] = waitList;
    data["buses"] = buses;
    storeData << data.dump(4);
    storeData.close();
}

bool Waitlist::processWaitlistSingle(string busID, int seatRefunded)
{
    loadData();
    json singleWait = waitList["singleWaitList"];
    int sWIdx = 0;
    for (auto &sW : singleWait)
    {
        if (sW["status"] == "active" && sW["busID"] == busID && sW["waitType"] == "any")
        {
            string userID = sW["userID"];
            int busIdx = 0;
            for (auto &bus : buses)
            {
                if (bus["id"] == busID)
                {
                    bus["seats"][seatRefunded - 1]["status"] = "reserved";
                    int seatLeft = bus["seatLeft"];
                    seatLeft--;
                    bus["seatLeft"] = seatLeft;

                    vector<int> seatNum;
                    seatNum.push_back(seatRefunded);
                    generateReservationFromWaitlist(busID, userID, seatNum);
                    sW["status"] = "inactive";
                    waitList["singleWaitList"][sWIdx] = sW;
                    storeDataWaitList();
                    return true;
                }
            }
        }
        else if (sW["status"] == "active" && sW["busID"] == busID && sW["waitType"] == "specific")
        {
            int specificSeatNum = sW["seatNumber"];
            string userID = sW["userID"];
            for (auto &bus : buses)
            {
                if (bus["id"] == busID && bus["seats"][specificSeatNum - 1]["status"] == "available")
                {
                    int seatLeft = bus["seatLeft"];
                    seatLeft--;
                    bus["seatLeft"] = seatLeft;
                    bus["seats"][specificSeatNum - 1]["status"] = "reserved";
                    vector<int> seatNum;
                    seatNum.push_back(specificSeatNum);
                    generateReservationFromWaitlist(busID, userID, seatNum);
                    sW["status"] = "inactive";
                    waitList["singleWaitList"][sWIdx] = sW;
                    storeDataWaitList();
                    return true;
                }
            }
        }
        sWIdx++;
    }
    return false;
}

bool Waitlist::processWaitlistBulk(string busID, vector<int> seatsRefunded)
{
    // [FOR FUTURE TO CHANGE]
    loadData();
    json bulkWait = waitList["bulkWaitList"];
    for (auto &bW : bulkWait)
    {
        if (bW["size"] == seatsRefunded.size())
        {
            if (bW["status"] == "active" && bW["busID"] == busID && bW["waitType"] == "any")
            {

                string userID = bW["userID"];
                for (auto &bus : buses)
                {
                    if (bus["id"] == busID)
                    {
                        int i = 0;
                        while (i < seatsRefunded.size())
                        {
                            bus["seats"][seatsRefunded[i]]["status"] = "reserved";
                            i++;
                        }
                        generateReservationFromWaitlist(busID, userID, seatsRefunded);
                        bW["status"] = "inactive";
                        storeDataWaitList();
                        return true;
                    }
                }
            }
            else if (bW["status"] == "active" && bW["busID"] == busID && bW["waitType"] == "specific")
            {
                if (bW["size"] == seatsRefunded.size() && bW["seatNumber"] == seatsRefunded)
                {
                    string userID = bW["userID"];
                    for (auto &bus : buses)
                    {
                        if (bus["id"] == busID)
                        {
                            int i = 0;
                            while (i < seatsRefunded.size())
                            {
                                bus["seats"][seatsRefunded[i]]["status"] = "reserved";
                                i++;
                            }
                            generateReservationFromWaitlist(busID, userID, seatsRefunded);
                            bW["status"] = "inactive";
                            storeDataWaitList();
                            return true;
                        }
                    }
                }
            }
        }
        else
        {
            cout << "\033[31mCannot reserve waitListed user \033[0m\n";
        }
    }
    return false;
}

void Waitlist::generateReservationFromWaitlist(string bID, string userID, vector<int> seatNums)
{
    time_t currentTime = time(nullptr);
    string time = ctime(&currentTime); // Convert to string
    time.pop_back();
    if (seatNums.size() == 1)
    {
        json singleRes = reservations["singleReservations"];
        json newResObj;
        int nextID = reservations["singleReservations"].size();
        string nextID_string = to_string(nextID);
        string baseResID = "R000000";

        int start = baseResID.size() - nextID_string.size();
        int j = 0;
        for (int i = start; i < baseResID.size(); i++)
        {
            baseResID[i] = nextID_string[j];
            j++;
        }

        newResObj["id"] = baseResID;
        newResObj["busID"] = bID;
        newResObj["seatNumber"] = seatNums.at(0);
        newResObj["userID"] = userID;
        newResObj["status"] = "active";
        newResObj["time"] = time;
        singleRes.push_back(newResObj);
        reservations["singleReservations"] = singleRes;

        for (auto &user : users)
        {
            if (user["id"] == userID)
            {
                user["resID"].push_back(baseResID);
            }
        }
    }
    // [TO CHANGE FOR THE FUTURE]
    // else
    // {
    //     json bulkRes = reservations["bulkReservations"];
    //     int nextID = reservations["bulkReservations"].size();
    //     string nextID_string = to_string(nextID);
    //     string baseResID = "RB000000";

    //     int start = baseResID.size() - nextID_string.size();
    //     int j = 0;
    //     for (int i = start; i < baseResID.size(); i++)
    //     {
    //         baseResID[i] = nextID_string[j];
    //         j++;
    //     }

    //     json newResObj;
    //     newResObj["id"] = baseResID;
    //     newResObj["busID"] = bID;
    //     newResObj["seatNumber"] = seatNums;
    //     newResObj["userID"] = userID;
    //     newResObj["status"] = "active";
    //     newResObj["time"] = time;
    //     bulkRes.push_back(newResObj);
    //     reservations["singleReservations"] = bulkRes;

    //     // adding the reservation id to the user
    //     for (auto &user : users)
    //     {
    //         if (user["id"] == userID)
    //         {
    //             user["resID"].push_back(baseResID);
    //         }
    //     }
    // }
}

#endif