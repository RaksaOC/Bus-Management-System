#ifndef User_hpp
#define User_hpp

#include <iostream>
#include <vector>
#include <limits>
#include <stack>
#include <ctime>
#include "Bus.hpp"
#include "menu.hpp"
#include "validation.hpp"
#include "./Waitlist.hpp"

#define dataFilePath "../utils/database/Data.json"

using json = nlohmann::json;
using namespace std;

// -------------------------------------------------------------------

class User
{
private:
    // user attributes =====================================================
    string userID;
    string name;
    string lastName;
    string firstName;
    int age;
    string email;
    string password;
    bool isAdmin;
    vector<string> resID; // Stores reservation IDs
    // For initially loading data ==========================================
    json data;
    json users;
    json buses;
    json reservations;
    json routes;

    // For partially changed data to be put back to file ===================
    json busToModify;
    json modifiedUser;

    // Helper Methods
    // Working with data
    void loadData();

    // reservation helper methods ==================
    //  show and input from, to
    void destinationMenu();
    string inputFrom();
    string inputTo(string);
    // show buses and bus selection based on search
    vector<int> showAvailableBuses(string, string);
    int printBus(json, string, string, int); // int *);
    Bus selectBus(vector<int>);
    // ============================================

    // refund helper methods ======================

    bool isResIDRefunded(string);
    int inputRefund();
    vector<string> refundList();
    string printRefund(string);
    vector<int> getSeatNumsToRefund(string);
    void generateNewResIDForRefund(string, vector<int>);

    // view history helper methods

    void printHistory(vector<int>, string, string);

    // After working with the bus object(reserve seat....)
    void generateResID(int, json, vector<int>, int);
    void generateTicket(vector<int>);
    void showQRCode();
    void storeData();

public:
    User() = default; // Default constructor

    // Constructor to initialize user data after authentication
    User(string UID, string fn, string ln, string n, int a, string em, string pswd, bool aS, vector<string> rID)
    {
        userID = UID;
        firstName = fn;
        lastName = ln;
        name = n;
        age = a;
        email = em;
        password = pswd;
        isAdmin = aS;
        resID = rID;
    }

    // Set and Get methods
    string getUID() { return userID; }
    string getName() { return name; }
    string getFirstName() { return firstName; }
    string getLastName() { return lastName; }
    int getAge() { return age; }
    string getEmail() { return email; }
    string getPassword() { return password; }
    bool getAdminStatus() { return isAdmin; };

    // check and redirect the user to be admin or normal user
    void checkUserType();

    // Core User Methods
    string reserve();     // Method for reserving a bus ticket
    string refund();      // Method for refunding a reservation
    string viewHistory(); // Method for viewing reservation history

    // Core Admin Methods
    void addAdmin();
    void addBus();
    void changeBusSettings();
    void getAllUsers();

    // Helper Functions
    void printUser();
};

void User::checkUserType()
{
    if (this->getAdminStatus()) // reference to menu.hpp
    {
        int choice = adminActionsMenu();
        switch (choice)
        {
        case 1:
            this->addAdmin();
            break;
        case 2:
            this->addBus();
            break;
        case 3:
            this->changeBusSettings();
            break;
        case 4:
            this->getAllUsers();
            break;
        default:
            break;
        }
    }
    else
    {
        while (true)
        {
            int choice = serviceMenu();
            while (true)
            {
                if (choice == 1)
                {
                    string back = this->reserve();
                    if (back == "-b")
                    {
                        break;
                    }
                    if (back == "") // successful
                    {
                        exit(8);
                    }
                }
                else if (choice == 2)
                {
                    string back = this->refund();
                    if (back == "-b")
                    {
                        break;
                    }
                    else if (back == "-n")
                    {
                        break;
                    }
                    else if (back == "")
                    {
                        exit(8);
                    }
                }
                else if (choice == 3)
                {
                    string back = this->viewHistory();
                    if (back == "-b")
                    {
                        break;
                    }
                }
            }
        }
    }
}

// Method for reserving a bus ticket

string User::reserve()
{
    loadData();
    destinationMenu();
    string from = inputFrom();
    if (from == "-b")
    {
        return "-b";
    }

    string to = inputTo(from);
    vector<int> busIdx = showAvailableBuses(from, to);
    Bus bus = selectBus(busIdx);

    if (bus.getSeatLeft() == 0)
    {
        return ""; // this is to check that its been waitListed
    }
    seatsMenu();
    bus.showSeatLayout();

    json chosenSeat;
    json seatsOfBus;
    vector<int> seatsChangedArr;
    chosenSeat["seatNum"] = -1;
    resTypeMenu();
    int bType = bookingTypeMenu();
    if (bType == 1)
    {
        chosenSeat = bus.reserveSeat();
        int seatIdx = 0;
        for (const auto &seat : busToModify["seats"])
        {
            if (seat["seatNum"] == chosenSeat["seatNum"])
            {
                busToModify["seats"][seatIdx] = chosenSeat;
                break;
            }
            seatIdx++;
        }
        // changing some attributes
        int seatLeft = busToModify["seatLeft"];
        seatLeft--;
        busToModify["seatLeft"] = seatLeft;
    }
    else if (bType == 2)
    {
        seatsOfBus = bus.reserveSeats();
        int seatLeft = bus.getSeatLeft();
        cout << seatLeft << endl;
        busToModify["seats"] = seatsOfBus;
        busToModify["seatLeft"] = seatLeft;
        seatsChangedArr = bus.getSeatNumChanges();
    }
    // changes the status of seat for the selected bus

    // finalizing file writing and reservation
    generateResID(chosenSeat["seatNum"], seatsOfBus, seatsChangedArr, bType);
    showQRCode();
    storeData();
    if (bType == 1)
    {
        vector<int> seatNum;
        seatNum.push_back(chosenSeat["seatNum"]);
        generateTicket(seatNum);
    }
    else
    {
        generateTicket(seatsChangedArr);
    }

    thankYouForTravelingWithUs();
    return "";
}

// // Method for refunding a reservation
string User::refund()
{
    loadData();
    if (!this->resID.empty())
    {
        vector<string> refundableResID = refundList();
        if (refundableResID.empty())
        {
            cout << "Error: No refundable tickets\n";
            return "";
        }

        int choice = inputRefund();
        if (choice == -1)
        {
            return "-b";
        }

        string resIDToRefund = refundableResID.at(choice - 1);
        vector<int> seatNumsToRefund = getSeatNumsToRefund(resIDToRefund);

        string busIDToRefund;

        // get the bus ID to refund
        if (isResIDBulk(resIDToRefund))
        {
            json bulkRes = reservations["bulkReservations"];
            for (auto &res : bulkRes)
            {
                if (res["id"] == resIDToRefund)
                {
                    busIDToRefund = res["busID"];
                }
            }
        }
        else
        {
            json singleRes = reservations["singleReservations"];
            for (auto &res : singleRes)
            {
                if (res["id"] == resIDToRefund)
                {
                    busIDToRefund = res["busID"];
                }
            }
        }

        // traverse to that bus and delegate to the bus class

        for (auto &bus : buses)
        {
            if (bus["id"] == busIDToRefund)
            {
                busToModify = bus;
                string busType = busToModify["busType"];
                string dpTime = busToModify["departureTime"];
                string busID = busToModify["id"];
                json route = busToModify["route"];
                int seatCap = busToModify["seatCap"];
                int seatLeft = busToModify["seatLeft"];
                int seatPrice = busToModify["seatPrice"];
                json seats = busToModify["seats"];
                Bus bus(busType, dpTime, busID, route, seatCap, seatLeft, seatPrice, seats);
                if (!isResIDBulk(resIDToRefund))
                {
                    json seatsOfModifiedBus = bus.refundSeat(seatNumsToRefund);

                    busToModify["seats"] = seatsOfModifiedBus;
                    int seatLeft = busToModify["seatLeft"]; // gain one seat
                    seatLeft++;
                    busToModify["seatLeft"] = seatLeft;
                    json singleRes = reservations["singleReservations"];
                    for (auto &res : singleRes)
                    {
                        if (res["id"] == resIDToRefund)
                        {
                            res["status"] = "inactive";
                            break;
                        }
                    }
                    reservations["singleReservations"] = singleRes;
                    seccessRefundMenu();
                    storeData();
                    Waitlist waitlist;
                    int seatNumRefunded = bus.getSeatNumChanges().at(0);
                    if (waitlist.processWaitlistSingle(busID, seatNumRefunded))
                    {
                        cout << "Your seat has been taken by a wait listed user\n";
                        return "";
                    }
                }
                else
                {
                    json seatsOfModifiedBus = bus.refundSeats(seatNumsToRefund);
                    busToModify["seats"] = seatsOfModifiedBus;
                    busToModify["seatLeft"] = bus.getSeatLeft();
                    vector<int> seatNumRemaining = bus.getSeatNumChanges();
                    generateNewResIDForRefund(busIDToRefund, seatNumRemaining);
                    json bulkRes = reservations["bulkReservations"];
                    for (auto &res : bulkRes)
                    {
                        if (res["id"] == resIDToRefund)
                        {
                            res["status"] = "inactive";
                            break;
                        }
                    }
                    reservations["bulkReservations"] = bulkRes;
                    storeData();
                    seccessRefundMenu();
                    // Waitlist waitlist;
                    // if (waitlist.processWaitlistBulk(busID, seatNumsToRefund)) // for refund all
                    // {
                    //     cout << "Your seats has been taken by a wait listed user\n";
                    //     return;
                    // }
                    // else if (waitlist.processWaitlistBulk(busID, bus.getWantedSeatNums())) // partial refund
                    // {
                    //     cout << "Your seats has been taken by a wait listed user\n";
                    //     return;
                    // }
                }
            }
        }
    }
    else
    {
        cout << "\033[31m [⚠️] Error: No Reservation History \033[0m\n";
        return "-n";
    }
    return "";
}

vector<int> User::getSeatNumsToRefund(string resID)
{
    vector<int> seatNumArrToReturn;
    if (!isResIDBulk(resID))
    {
        json singleRes = reservations["singleReservations"];
        for (auto &r : singleRes)
        {
            if (r["id"] == resID)
            {
                seatNumArrToReturn.push_back(r["seatNumber"]);
                return seatNumArrToReturn;
            }
        }
    }
    else
    {
        json bulkRes = reservations["bulkReservations"];
        for (auto &r : bulkRes)
        {
            if (r["id"] == resID)
            {
                seatNumArrToReturn = r["seatNumber"].get<vector<int>>();
                return seatNumArrToReturn;
            }
        }
    }
    return seatNumArrToReturn;
}

vector<string> User::refundList()
{
    vector<string> allRes;
    vector<string> validRes;
    stack<string> resIDStack;
    for (string r : resID)
    {
        resIDStack.push(r);
    }
    cout << "\n\033[33mRDERED BY LATEST \033[0m\n\n";
    while (!resIDStack.empty())
    {
        allRes.push_back(printRefund(resIDStack.top()));
        resIDStack.pop();
    }
    for (string i : allRes)
    {
        if (i != "")
        {
            validRes.push_back(i);
        }
    }

    return validRes;
}

bool User::isResIDRefunded(string resID)
{
    if (isResIDBulk(resID))
    {
        json bulkRes = reservations["bulkReservations"];
        for (const auto &res : bulkRes)
        {
            if (res["id"] == resID)
            {
                if (res["status"] == "inactive")
                {
                    return true;
                }
            }
        }
    }
    else
    {
        json singleRes = reservations["singleReservations"];
        for (const auto &sR : singleRes)
        {
            if (sR["id"] == resID)
            {
                if (sR["status"] == "inactive")
                {
                    return true;
                }
            }
        }
    }
    return false;
}

string User::printRefund(string resID)
{
    if (!isResIDRefunded(resID))
    {
        if (isResIDBulk(resID))
        {
            json bulkRes = reservations["bulkReservations"];
            for (const auto &bR : bulkRes)
            {
                if (bR["id"] == resID)
                {
                    vector<int> seatNums = bR["seatNumber"];
                    string busIDToCheck = bR["busID"];
                    for (const auto &bus : buses)
                    {
                        if (bus["id"] == busIDToCheck)
                        {
                            cout << "Time: " << bR["time"] << "\n";
                            cout << "\033[36m***************************************** \033[0m" << endl;
                            cout << "\033[36m* Reservation ID: \033[0m" << resID << "\t\t\033[36m*\033[0m" << endl;
                            cout << "\033[36m* Type: \033[0m" << bus["busType"] << "\t\t\t\033[36m*\033[0m" << endl;
                            cout << "\033[36m* Bus ID: \033[0m" << bus["id"] << "\t\t\t\033[36m*\033[0m" << endl;
                            cout << "\033[36m* Departure time: \033[0m" << bus["departureTime"] << "\t\033[36m*\033[0m" << endl;
                            cout << "\033[36m* From: \033[0m" << bus["route"]["from"] << "\t\t\t\033[36m*\033[0m" << endl;
                            cout << "\033[36m* To: \033[0m" << bus["route"]["to"] << "\t\t\t\033[36m*\033[0m" << endl;
                            cout << "\033[36m* Booked Seat numbers: \033[0m";
                            for (int s : seatNums)
                            {
                                cout << s << " ";
                            }
                            cout << "\t\t\t\033[36m*" << endl;
                            cout << "\033[36m***************************************** \033[0m" << endl;
                            cout << endl;
                            return resID;
                        }
                    }
                }
            }
        }
        else
        {
            json singleRes = reservations["singleReservations"];
            for (const auto &sR : singleRes)
            {
                if (sR["id"] == resID)
                {
                    int seatNum = sR["seatNumber"];
                    string busIDToCheck = sR["busID"];
                    for (const auto &bus : buses)
                    {
                        if (bus["id"] == busIDToCheck)
                        {
                            cout << "Time: " << sR["time"] << "\n";
                            cout << "\033[36m***************************************** \033[0m" << endl;
                            cout << "\033[36m* \033[0m\033[36mReservation ID:\033[0m " << resID << "\t\t\033[36m*\033[0m" << endl;
                            cout << "\033[36m* \033[0m\033[36mType:\033[0m " << bus["busType"] << "\t\t\t\033[36m*\033[0m" << endl;
                            cout << "\033[36m* \033[0m\033[36mBus ID:\033[0m " << bus["id"] << "\t\t\t\033[36m*\033[0m" << endl;
                            cout << "\033[36m* \033[0m\033[36mDeparture time:\033[0m " << bus["departureTime"] << "\t\033[36m*\033[0m" << endl;
                            cout << "\033[36m* \033[0m\033[36mFrom:\033[0m " << bus["route"]["from"] << "\t\t\t\033[36m*\033[0m" << endl;
                            cout << "\033[36m* \033[0m\033[36mTo:\033[0m " << bus["route"]["to"] << "\t\t\t\033[36m*\033[0m" << endl;
                            cout << "\033[36m* \033[0m\033[36mBooked Seat number:\033[0m " << seatNum;
                            cout << "\t\t\t\033[36m*" << endl;
                            cout << "\033[36m***************************************** \033[0m" << endl;
                            cout << endl;
                            return resID;
                        }
                    }
                }
            }
        }
    }
    else
    {
        return "";
    }
    return "";
}

int User::inputRefund()
{
    int choice;
    while (1)
    {
        cout << "Select the ticket to refund\n\n> ";
        cin >> choice;
        if (choice == -1)
        {
            return -1;
        }

        if (choice <= 0 || choice > this->resID.size())
        {
            cout << "Error: Invalid choice" << endl;
        }
        else
        {
            break;
        }
    }

    return choice;
}

string User::viewHistory()
{
    loadData();
    stack<string> resIDStack;

    // Push all reservation IDs into the stack
    for (auto &res : this->resID)
    {
        resIDStack.push(res);
    }
    if (resIDStack.empty())
    {
        cout << "Error: No reservation history\n";
        return "";
    }

    // Process each reservation ID from the stack
    cout << "\n\n\033[36m ORDERED BY LATEST\033[0m\n\n";
    while (!resIDStack.empty())
    {
        string topResID = resIDStack.top();

        if (isResIDBulk(topResID))
        {
            json bulkRes = reservations["bulkReservations"];
            for (const auto &res : bulkRes)
            {
                if (res["id"] == topResID)
                {
                    string busID = res["busID"];
                    vector<int> seatNums = res["seatNumber"];
                    string status = res["status"];
                    cout << "Time: " << res["time"] << "\n";
                    printHistory(seatNums, busID, status);
                }
            }
        }
        else
        {
            json singleRes = reservations["singleReservations"];
            for (const auto &res : singleRes)
            {
                if (res["id"] == topResID) // Fixed comparison
                {
                    string busID = res["busID"];
                    vector<int> seatNum;
                    string status = res["status"];
                    seatNum.push_back(res["seatNumber"]);
                    cout << "Time: " << res["time"] << "\n";
                    printHistory(seatNum, busID, status);
                }
            }
        }

        resIDStack.pop();
    }
    string back;
    cout << "> ";
    cin >> back;
    return back;
}

void User::printHistory(vector<int> seatNums, string bID, string status)
{
    json busInfo;
    for (const auto &bus : buses)
    {
        if (bus["id"] == bID)
            busInfo = bus;
    }

    cout << "\033[36m***************************************** \033[0m" << endl;
    cout << "\033[36m* \033[0m\033[36mType:\033[0m " << busInfo["busType"] << "\t\t\t\033[36m*\033[0m" << endl;
    cout << "\033[36m* \033[0m\033[36mBus ID:\033[0m " << busInfo["id"] << "\t\t\t\033[36m*\033[0m" << endl;
    cout << "\033[36m* \033[0m\033[36mDeparture time:\033[0m " << busInfo["departureTime"] << "\t\033[36m*\033[0m" << endl;
    cout << "\033[36m* \033[0m\033[36mFrom:\033[0m " << busInfo["route"]["from"] << "\t\t\t\033[36m*\033[0m" << endl;
    cout << "\033[36m* \033[0m\033[36mTo:\033[0m " << busInfo["route"]["to"] << "\t\t\t\033[36m*\033[0m" << endl;
    cout << "\033[36m* \033[0m\033[36mSeat numbers:\033[0m ";
    for (int s : seatNums)
    {
        cout << s << " ";
    }
    cout << "\t\t\t\033[36m*\033[0m" << endl
         << "\033[36m* \033[0m\033[36mStatus:\033[0m " << status << "\t\t\t\033[36m*\033[0m" << endl;
    cout << "\033[36m***************************************** \033[0m" << endl
         << endl;
}

// ADMIN ACTIONS ===================================================================

void User::addAdmin() {}
void User::addBus() {}
void User::changeBusSettings() {}
void User::getAllUsers() {}

// helper methods for Reserve ============================================================

void User::loadData()
{
    ifstream readData(dataFilePath);
    if (!readData.is_open())
    {
        cerr << openFileFailMessage;
        cerr << dataFilePath;
        return;
    }
    json allData;
    readData >> allData;
    this->data = allData;
    this->users = allData["users"];
    this->buses = allData["buses"];
    this->reservations = allData["reservations"];
    this->routes = allData["routes"];
}

void User::destinationMenu()
{
    cout << R"(
                                      ╔═╗╦  ╦╔═╗╦  ╔═╗╔╗ ╦  ╔═╗  ╦═╗╔═╗╦ ╦╔╦╗╔═╗╔═╗
                                      ╠═╣╚╗╔╝╠═╣║  ╠═╣╠╩╗║  ║╣   ╠╦╝║ ║║ ║ ║ ║║╣╚═╗
                                      ╩ ╩ ╚╝ ╩ ╩╩═╝╩ ╩╚═╝╩═╝╚═╝  ╩╚═╚═╝╚═╝ ╩ ╚═╝╚═╝
    )";
    cout << "\n\n";
    cout << "\t\t\t      \033[36m***********************************************************\033[0m" << endl;
    for (const auto &route : routes)
    {
        for (const auto &to : route["to"])
        {
            cout << "\t\t\t      \033[36m*\033[0m\t" << route["from"] << "\t\t\033[36m------->\033[0m\t" << to << "\033[36m\t*\033[0m" << endl;
        }
    }
    cout << "\t\t\t      \033[36m***********************************************************\033[0m" << endl;
}

string User::inputFrom()
{
    string from;
    while (1)
    {
        cout << "\033[36mFrom\n\n\033[0m> ";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer
        getline(cin, from);
        if (from == "-b")
        {
            return "-b";
        }

        if (isFromValid(from, routes))
        {
            break;
        }
        else
        {
            cout << invalidInputMessage;
        }
    }
    return from;
}

string User::inputTo(string from)
{
    string to;
    while (1)
    {
        cout << "\n\033[36mTo\n\n\033[0m> ";
        getline(cin, to);
        if (isToValid(from, to, routes))
        {
            break;
        }
        else
        {
            cout << invalidDestinationMessage;
        }
    }
    return to;
}
vector<int> User::showAvailableBuses(string f, string t)
{
    availableBusMenu();
    vector<int> allIndex;
    vector<int> validIndex;
    int busIdx = 0;
    int correctCount = 0; // Variable to count the number of correct buses

    for (const auto &bus : buses)
    {
        allIndex.push_back(printBus(bus, f, t, busIdx)); //));
        busIdx++;
    }
    // allIdx contains [-1-1-1-1-,4,5,-1-1,8] which means that the numbers that are -1 are the buses
    // that doesn't meet the requirement but the valid numbers are the index of the correct bus
    // so then we refine this array to contain the valid indexes
    int j = 0;
    for (int i : allIndex)
    {
        if (i != -1)
        {
            validIndex.push_back(allIndex[j]);
        }
        j++;
    }

    return validIndex;
}

int User::printBus(json bus, string f, string t, int i) // int *correctCount)
{
    if (bus["route"]["from"] == f && bus["route"]["to"] == t)
    {
        // correctCount++; // Increment the count of correct buses
        cout << "\n\033[36mBus \033[0m" << "\n\n";
        cout << "\033[36m***************************************** \033[0m" << endl;
        cout << "\033[36m* \033[0m\033[36mID:\033[0m " << bus["id"] << "\t\t\t\t*" << endl;
        cout << "\033[36m* \033[0m\033[36mType:\033[0m " << bus["busType"] << "\t\t\t*" << endl;
        cout << "\033[36m* \033[0m\033[36mDeparture:\033[0m " << bus["departureTime"] << "\t\t*" << endl;
        cout << "\033[36m* \033[0m\033[36mNumber of Seats:\033[0m " << bus["seatCap"] << "\t\t\t*" << endl;
        cout << "\033[36m* \033[0m\033[36mRemaining Seats:\033[0m " << bus["seatLeft"] << "\t\t\t*" << endl;
        cout << "\033[36m* \033[0m\033[36mPrice:\033[0m $" << bus["seatPrice"] << "\t\t\t\t*" << endl;
        cout << "\033[36m***************************************** \033[0m" << endl;
        return i; // Return the index of the correct bus
    }
    return -1; // Return -1 if the bus doesn't match
}

Bus User::selectBus(vector<int> busIdxArr)
{
    int choice;
    while (1)
    {
        cout << "\033[36m\nSelect a bus \033[0m \n\n> ";
        cin >> choice;
        if (choice < 0 || choice > busIdxArr.size())
        {
            cout << invalidInputMessage;
            continue;
        }

        choice = choice - 1;
        int busIndex = busIdxArr[choice];

        busToModify = buses[busIndex];
        if (busToModify["seatLeft"] == 0)
        {
            cout << "\033[31mThere are no more seats available \033[0m\n";
            Waitlist waitlist;
            int waitChoice = waitlist.choiceToEnterWaitlist();
            if (waitChoice == 1)
            {
                string busType = busToModify["busType"];
                string dpTime = busToModify["departureTime"];
                string busID = busToModify["id"];
                json route = busToModify["route"];
                int seatCap = busToModify["seatCap"];
                int seatLeft = busToModify["seatLeft"];
                int seatPrice = busToModify["seatPrice"];
                json seats = busToModify["seats"];

                Bus bus(busType, dpTime, busID, route, seatCap, seatLeft, seatPrice, seats);
                bus.printBusInfo();
                bus.showSeatLayoutBlank();
                waitlist.addToWaitlist(this->userID, busID);
                addedToWaitListMenu();
                return bus;
            }
            else
            {
                continue;
            }
        }
        else
        {
            break;
        }
    }

    string busType = busToModify["busType"];
    string dpTime = busToModify["departureTime"];
    string busID = busToModify["id"];
    json route = busToModify["route"];
    int seatCap = busToModify["seatCap"];
    int seatLeft = busToModify["seatLeft"];
    int seatPrice = busToModify["seatPrice"];
    json seats = busToModify["seats"];

    Bus bus(busType, dpTime, busID, route, seatCap, seatLeft, seatPrice, seats);
    bus.printBusInfo();
    return bus;
}

void User::generateResID(int seatNum, json seatsOfBus, vector<int> seatChanges, int bType)
{
    time_t currentTime = time(nullptr);
    string time = ctime(&currentTime); // Convert to string
    time.pop_back();
    if (bType == 1)
    {
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

        json newResObj;
        newResObj["id"] = baseResID;
        newResObj["busID"] = busToModify["id"];
        newResObj["seatNumber"] = seatNum;
        newResObj["userID"] = this->userID;
        newResObj["status"] = "active";
        newResObj["time"] = time;

        this->resID.push_back(baseResID);
        reservations["singleReservations"].push_back(newResObj);
    }
    else if (bType == 2)
    {
        int nextID = reservations["bulkReservations"].size();
        string nextID_string = to_string(nextID);
        string baseResID = "RB000000";

        int start = baseResID.size() - nextID_string.size();
        int j = 0;
        for (int i = start; i < baseResID.size(); i++)
        {
            baseResID[i] = nextID_string[j];
            j++;
        }
        vector<int> seatNumbers;
        for (int i = 0; i < seatChanges.size(); i++)
        {
            seatNumbers.push_back(seatChanges.at(i));
        }

        json newResObj;
        newResObj["id"] = baseResID;
        newResObj["busID"] = busToModify["id"];
        newResObj["seatNumber"] = seatNumbers;
        newResObj["userID"] = this->userID;
        newResObj["status"] = "active";
        newResObj["time"] = time;
        this->resID.push_back(baseResID);
        reservations["bulkReservations"].push_back(newResObj);
    }
}
void User::showQRCode()
{
    cout << "\n\nProceeding to payment... Please scan the QR code.\n";
    system("open ../../qr.jpg");
}

void User::generateTicket(vector<int> seatNum)
{
    int price = busToModify["seatPrice"];
    price *= seatNum.size();
    cout << R"(            
                                                ╔╦╗╦╔═╗╦╔═╔═╗╔╦╗
                                                 ║ ║║  ╠╩╗║╣  ║ 
                                                 ╩ ╩╚═╝╩ ╩╚═╝ ╩  
    )" << endl;
    cout << "\033[36m***************************************** \033[0m" << "\t\t\t" << endl;
    cout << "\033[36m* \033[0m\033[36mReservation ID:\033[0m " << modifiedUser["resID"][modifiedUser["resID"].size() - 1] << "\t\t*" << endl;
    cout << "\033[36m* \033[0m\033[36mBus ID:\033[0m " << busToModify["id"] << "\t\t\t*" << endl;
    cout << "\033[36m* \033[0m\033[36mBus Type:\033[0m " << busToModify["busType"] << "\t\t*" << endl;
    cout << "\033[36m* \033[0m\033[36mPrice per seat:\033[0m $" << busToModify["seatPrice"] << "\t\t\t*" << endl;
    cout << "\033[36m* \033[0m\033[36mDeparture Time:\033[0m " << busToModify["departureTime"] << "\t*" << endl;

    // Print route details
    cout << "\033[36m* \033[0m\033[36mFrom:\033[0m " << busToModify["route"]["from"] << "\t\t\t*" << endl;
    cout << "\033[36m* \033[0m\033[36mTo:\033[0m " << busToModify["route"]["to"] << "\t\t\t*" << endl;

    // Print seat details
    cout << "\033[36m* \033[0m\033[36mSeat Number:\033[0m ";
    for (int s : seatNum)
    {
        cout << s << " ";
    }
    cout << "\t\t\t*" << endl
         << "\033[36m* \033[0m\033[36mTotal Price:\033[0m $" << price * seatNum.size() << "\t\t\t*" << endl;
    cout << "\033[36m***************************************** \033[0m" << "\t\t\t" << endl;

    cout << "\n\n\n";
}

void User::storeData()
{
    int busIdx = 0;
    for (const auto &bus : buses)
    {
        if (bus["id"] == busToModify["id"])
        {
            break;
        }
        busIdx++;
    }

    buses[busIdx] = busToModify;
    modifiedUser["age"] = this->age;
    modifiedUser["email"] = this->email;
    modifiedUser["id"] = this->userID;
    modifiedUser["isAdmin"] = this->isAdmin;
    modifiedUser["name"]["firstName"] = this->firstName;
    modifiedUser["name"]["lastName"] = this->lastName;
    modifiedUser["password"] = this->password;
    modifiedUser["resID"] = this->resID;

    int userIdx = 0;
    for (const auto &user : users)
    {
        if (user["id"] == this->userID)
        {
            break;
        }
        userIdx++;
    }

    users[userIdx] = modifiedUser;
    data["users"] = users;
    data["buses"] = buses;
    data["reservations"] = reservations;

    ofstream storeFile(dataFilePath);
    if (!storeFile.is_open())
    {
        cerr << openFileFailMessage;
        cerr << dataFilePath;
    }

    storeFile << data.dump(4);
    storeFile.close();
}

void User::printUser()
{
    cout << "User ID: " << this->getUID() << endl;
    cout << "First Name: " << this->getFirstName() << endl;
    cout << "Last Name: " << this->getLastName() << endl;
    cout << "Name: " << this->getName() << endl;
    cout << "Age: " << this->getAge() << endl;
    cout << "Email: " << this->getEmail() << endl;
    cout << "Password: " << this->getPassword() << endl;
    cout << "Is Admin: " << this->getAdminStatus() << endl;
}
// End of helper methods for Reserve =============================================================

void User::generateNewResIDForRefund(string busID, vector<int> seatNums)
{
    if (seatNums.size() > 1)
    {
        time_t currentTime = time(nullptr);
        string time = ctime(&currentTime); // Convert to string
        time.pop_back();
        json bulkRes = reservations["bulkReservations"];

        // block to generate resID
        string baseID = "RB000000";
        int lastId = bulkRes.size();
        string lastID_string = to_string(lastId);
        int start = baseID.size() - lastID_string.size();
        int j = 0;
        for (int i = start; i < baseID.size(); i++)
        {
            baseID[i] = lastID_string[j];
            j++;
        }

        json newResObj;
        newResObj["busID"] = busID;
        newResObj["id"] = baseID;
        newResObj["seatNumber"] = seatNums;
        newResObj["status"] = "active";
        newResObj["time"] = time;
        newResObj["userID"] = this->userID;
        bulkRes.push_back(newResObj);
        reservations["bulkReservations"] = bulkRes;
        this->resID.push_back(baseID);
    }
    else if (seatNums.size() == 1 && seatNums.at(0) != -1)
    {
        time_t currentTime = time(nullptr);
        string time = ctime(&currentTime); // Convert to string
        time.pop_back();
        json singleRes = reservations["singleReservations"];

        // block to generate resID
        string baseID = "R000000";
        int lastId = singleRes.size();
        string lastID_string = to_string(lastId);
        int start = baseID.size() - lastID_string.size();
        int j = 0;
        for (int i = start; i < baseID.size(); i++)
        {
            baseID[i] = lastID_string[j];
            j++;
        }
        int seatNum = seatNums.at(0);
        json newResObj;
        newResObj["busID"] = busID;
        newResObj["id"] = baseID;
        newResObj["seatNumber"] = seatNum;
        newResObj["status"] = "active";
        newResObj["time"] = time;
        newResObj["userID"] = this->userID;
        singleRes.push_back(newResObj);
        reservations["singleReservations"] = singleRes;
        this->resID.push_back(baseID);
    }
    else
    {
        return;
    }
}

#endif