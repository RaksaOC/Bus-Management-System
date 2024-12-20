#ifndef User_hpp
#define User_hpp

#include <iostream>
#include <vector>
#include <limits>
#include <stack>
#include <ctime>
#include "Bus.hpp"
#include "./Waitlist.hpp"
#include "menu.hpp"
#include "validation.hpp"
#include "../libs/sha1.hpp"

#define dataFilePath "../utils/database/Data.json"

using json = nlohmann::json;
using namespace std;

// -------------------------------------------------------------------

class User
{
private:
    // cheating variable
    int correctCount = 0;

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

    // function for supporting the add-admin function
    string inputFirstName();
    string inputLastName();
    int inputAge();
    string inputEmail();
    string inputPassword();
    string confirmPassword(string);

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
    void storeDataAdmin();

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
    void deleteBus();
    void viewBus();
    void viewAllBus();
    void viewBusbyID();
    void getAllUsers();
    void deleteUser();

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
            this->viewBus();
            break;
        case 4:
            this->getAllUsers();
            break;
        case 5:
            this->deleteUser();
            break;
        case 6:
            this->deleteBus();
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
                    if (back == "-b" || back == "-n")
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
    simpleBusLoading();
    destinationMenu();
    string from = inputFrom();
    if (from == "-b")
    {
        return "-b";
    }

    string to = inputTo(from);
    simpleBusLoading();
    vector<int> busIdx = showAvailableBuses(from, to);
    Bus bus = selectBus(busIdx);

    if (bus.getSeatLeft() == 0)
    {
        return ""; // this is to check that its been waitListed
    }
    
    // asciiArt
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
    simpleBusLoading();
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
    simpleBusLoading();
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
        simpleBusLoading();
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
    cout << "\n\033[33mORDERED BY LATEST \033[0m\n\n";
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
                            correctCount++;
                            cout << "\033[36m* Ticket: \033[0m" << correctCount << endl;
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
    simpleBusLoading();
    // Push all reservation IDs into the stack
    for (auto &res : this->resID)
    {
        resIDStack.push(res);
    }
    if (resIDStack.empty())
    {
        cout << "\033[31m\n\n[⚠️] Error: No reservation history\033[0m\n";
        return "-n";
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

void User::addAdmin()
{
    cout << "\t\t\t\tNEW ADMIN\n\n";
    // [TO DO] Define the functionality to add an admin
    string fName = inputFirstName();
    string lName = inputLastName();
    int age = inputAge();
    string email = inputEmail();
    string pass = inputPassword();
    string passCf = confirmPassword(pass);
    passCf = hashPassword(passCf);

    ifstream readFile(dataFile);
    if (!readFile.is_open())
    {
        cerr << "\n Error cannot open:" << dataFile;
    }
    json allData;
    readFile >> allData;
    readFile.close();

    json userData = allData["users"];
    int lastID = userData.size();
    string fullID = "U000000";
    string lastID_string = to_string(lastID);
    int start = fullID.size() - lastID_string.size();

    for (int i = 0; i < lastID_string.size(); i++)
    {
        fullID[start + i] = lastID_string[i];
    }

    json newUser;
    newUser["id"] = fullID;
    newUser["name"]["firstname"] = fName;
    newUser["name"]["lasttname"] = lName;
    newUser["age"] = age;
    newUser["email"] = email;
    newUser["password"] = passCf;
    newUser["isAdmin"] = true;
    newUser["resID"] = json::array();
    allData["users"].push_back(newUser);

    ofstream writeFile(dataFile);
    if (!writeFile.is_open())
    {
        cerr << "Error: cannot open file" << dataFile;
    }
    writeFile << allData.dump(4);
    writeFile.close();

    cout << "Admin user added successfully!" << endl;
}
void User::addBus()
{
    loadData();
    string busType;
    string busID;
    string departureTime;
    string from;
    string to;
    int seatCap;
    int price;
    cout << "Enter bus type\n> ";
    cin >> busType;
    cout << "Enter departure time\n> ";
    cin >> departureTime;
    cout << "Enter Route ";
    cout << "From\n> ";
    cin >> from;
    cout << "To\n> ";
    cin >> to;
    cout << "Enter seat cap\n> ";
    cin >> seatCap;
    cout << "Enter Price\n> ";
    cin >> price;
    // generate new busID
    string baseID = "B0000";
    int lastID = buses.size();
    lastID++;
    string lastID_string = to_string(lastID);
    int start = baseID.size() - lastID_string.size();
    int j = 0;
    for (int i = start; i < baseID.size(); i++)
    {
        baseID[i] = lastID_string[j];
        j++;
    }
    // base id changed
    // new busID = baseID
    json newBus;
    newBus["busType"] = busType;
    newBus["departureTime"] = departureTime;
    newBus["id"] = baseID;
    newBus["route"]["from"] = from;
    newBus["route"]["to"] = to;
    newBus["seatCap"] = seatCap;
    newBus["seatLeft"] = seatCap;
    newBus["seatPrice"] = price;
    newBus["seats"];
    json seatOfBus;
    for (int i = 0; i < seatCap; i++)
    {
        seatOfBus["seatNum"] = i + 1;
        seatOfBus["status"] = "available";
        newBus["seats"].push_back(seatOfBus);
    }
    buses.push_back(newBus);
    storeDataAdmin();
}
void User::deleteBus()
{
    // delete bus
    string busID;
    cout << "PLease input bus id you want to delete" << endl;
    cin >> busID;

    bool isFound = false;
    char confirm;
    loadData();
    for (auto it = buses.begin(); it != buses.end(); ++it)
    {
        if ((*it)["id"] == busID)
        {
            isFound = true;

            cout << "Bus found:" << endl;
            cout << endl
                 << endl
                 << "----------------------Bus-----------------------" << endl
                 << endl;
            cout << "ID: " << (*it)["id"] << endl;
            cout << "Bus Type: " << (*it)["busType"] << endl;
            cout << "DepartureTime: " << (*it)["departureTime"] << endl;
            cout << "route: " << (*it)["route"]["from"] << "to " << (*it)["route"]["to"] << endl;
            cout << "Seat Capacity: " << (*it)["seatCap"] << endl;
            cout << "Seat left: " << (*it)["seatLeft"] << endl;
            cout << "Seat price: " << (*it)["seatPrice"] << "$" << endl;
            cout << endl
                 << "__________________________________________________" << endl
                 << endl;

            if ((*it)["seatLeft"] != (*it)["seatCap"])
            {
                cout << endl
                     << "Cannot delete bus " << busID << " because it have active reservations." << endl;
                break;
            }

            cout << "Are you sure you want to delete this user with ID " << userID << " (y/n)? ";
            cin >> confirm;

            if (confirm == 'y' || confirm == 'Y')
            {
                buses.erase(it);
                cout << "Bus deleted successfully." << endl;

                data["buses"] = buses;

                ofstream writeData(dataFilePath);
                if (!writeData.is_open())
                {
                    cerr << "Error: Unable to save changes to file." << endl;
                }
                else
                {
                    writeData << data.dump(4);
                    writeData.close();
                    cout << "Changes saved to file." << endl;
                }
            }
            else
            {

                cout << "Bus deletion canceled." << endl;
            }
            break;
        }
    }
    if (!isFound)
    {
        cout << "Bus does not exist" << endl;
    }
}

void User::getAllUsers()
{
    int option;
    string userID;
    bool isFound = false;
    loadData();

    // Option selection loop
    while (true)
    {
        cout << "Please input option (1/2):" << endl;
        cout << "1/ View one user by input their ID." << endl;
        cout << "2/ View all the existing users." << endl;
        cout << "Input here: ";
        cin >> option;

        // Check if the option is valid
        if (option < 1 || option > 2)
        {
            cout << "Invalid option, please try again." << endl;
            continue;
        }
        break; // Exit the loop if option is valid
    }

    // Option 1: View a user by ID
    if (option == 1)
    {
        while (true)
        {
            cout << "Please input user ID: ";
            cin >> userID;

            // Validate userID length and format
            if (userID.length() != 7)
            {
                cerr << "Invalid length: " << userID << endl;
                continue;
            }
            if (userID[0] != 'U')
            {
                cerr << "Invalid format: Does not start with 'U'" << endl;
                continue;
            }

            // for search for the user
            isFound = false;
            for (auto it = users.begin(); it != users.end(); ++it)
            {
                if ((*it)["id"] == userID)
                {
                    isFound = true;
                    // Print user information if found
                    cout << "\n\nUser found:\n"
                         << endl;
                    cout << endl
                         << endl
                         << "----------------------Users-----------------------" << endl
                         << endl;
                    cout << "ID: " << (*it)["id"] << endl;
                    cout << "Name: " << (*it)["name"]["firstName"] << " " << (*it)["name"]["lastName"] << endl;
                    cout << "Age: " << (*it)["age"] << endl;
                    cout << "Email: " << (*it)["email"] << endl;
                    cout << "Is Admin: " << (*it)["isAdmin"] << endl;
                    cout << "Password: " << (*it)["password"] << endl;
                    cout << "Reservation: " << (*it)["resID"] << endl;
                    cout << endl
                         << "__________________________________________________" << endl
                         << endl;
                    break; // Break loop after finding the user
                }
            }

            if (!isFound)
            {
                cout << "User does not exist." << endl
                     << "Please try again" << endl;
                continue;
            }
            break;
        }
    }
    // Option 2: View all users
    else
    {
        cout << endl
             << endl
             << "----------------------All Users-------------------------" << endl
             << endl;
        for (const auto &user : users)
        {
            cout << "ID: " << user["id"] << endl;
            cout << "Name: " << user["name"]["firstName"] << " " << user["name"]["lastName"] << endl;
            cout << "Age: " << user["age"] << endl;
            cout << "Email: " << user["email"] << endl;
            cout << "Is Admin: " << user["isAdmin"] << endl;
            cout << "Password: " << user["password"] << endl;
            cout << "Reservation: " << user["resID"] << endl;
            cout << endl
                 << "__________________________________________________" << endl
                 << endl;
        }
    }
}

void User::deleteUser()
{
    string userID;
    cout << "Please input the user ID you want to delete: " << endl;
    cin >> userID;

    loadData();

    bool isFound = false;
    char confirm;

    for (auto it = users.begin(); it != users.end(); ++it)
    {
        if ((*it)["id"] == userID)
        {
            isFound = true;

            cout << "User found:" << endl;
            cout << "ID: " << (*it)["id"] << endl;
            cout << "Name: " << (*it)["name"]["firstName"] << " " << (*it)["name"]["lastName"] << endl;
            cout << "Age: " << (*it)["age"] << endl;
            cout << "Email: " << (*it)["email"] << endl;
            cout << "Is Admin: " << (*it)["isAdmin"] << endl;
            cout << "Password: " << (*it)["password"] << endl;
            cout << "Reservation: " << (*it)["resID"] << endl;

            if (!(*it)["resID"].empty())
            {
                cout << "Cannot delete user " << userID << " because they have active reservations." << endl;
                break;
            }

            cout << "Are you sure you want to delete this user with ID " << userID << " (y/n)? ";
            cin >> confirm;

            if (confirm == 'y' || confirm == 'Y')
            {

                users.erase(it);
                cout << "User deleted successfully." << endl;

                data["users"] = users;

                ofstream writeData(dataFilePath);
                if (!writeData.is_open())
                {
                    cerr << "Error: Unable to save changes to file." << endl;
                }
                else
                {
                    writeData << data.dump(4);
                    writeData.close();
                    cout << "Changes saved to file." << endl;
                }
            }
            else
            {

                cout << "User deletion canceled." << endl;
            }
            break;
        }
    }

    if (!isFound)
    {
        cout << "User does not exist." << endl;
    }
}

void User::viewAllBus()
{
    cout << endl
         << endl
         << "----------------------All Buses-------------------------" << endl
         << endl;
    loadData();
    for (const auto &bus : buses)
    {
        cout << "Bus Type: " << bus["busType"] << endl;
        cout << "ID: " << bus["id"] << endl;
        cout << "Departure Time: " << bus["departureTime"] << endl;
        cout << "Route: " << bus["route"]["from"] << " to " << bus["route"]["to"] << endl;
        cout << "Seat Cap: " << bus["seatCap"] << endl;
        cout << "Seat Left: " << bus["seatLeft"] << endl;
        cout << "Seat Price: " << bus["seatPrice"] << endl;
        cout << endl
             << endl
             << "__________________________________________________" << endl
             << endl;
        ;
    }
}
void User::viewBusbyID()
{
    string busID;
    cout << "Please Input the Bus you want to find: ";
    cin >> busID;
    bool isFound = false;
    char confirm;
    loadData();
    for (auto it = buses.begin(); it != buses.end(); ++it)
    {
        if ((*it)["id"] == busID)
        {
            isFound = true;
            cout << "Bus found:" << endl;
            cout << endl
                 << endl
                 << "----------------------Bus-----------------------" << endl
                 << endl;
            cout << "ID: " << (*it)["id"] << endl;
            cout << "Bus Type: " << (*it)["busType"] << endl;
            cout << "DepartureTime: " << (*it)["departureTime"] << endl;
            cout << "route: " << (*it)["route"]["from"] << "to " << (*it)["route"]["to"] << endl;
            cout << "Seat Capacity: " << (*it)["seatCap"] << endl;
            cout << "Seat left: " << (*it)["seatLeft"] << endl;
            cout << "Seat price: " << (*it)["seatPrice"] << endl;
            cout << endl
                 << "__________________________________________________" << endl
                 << endl;
            break;
        }
    }
    if (!isFound)
    {
        cout << "ID is invalid." << endl;
    }
}

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
    //ascii art
    availableBusMenu();

    vector<int> allIndex;
    vector<int> validIndex;
    int busIdx = 0;

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
        correctCount++; // Increment the count of correct buses
        cout << "\n\033[36mBus \033[0m" << correctCount << " \n\n";
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
    simpleBusLoading();
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

void User::storeDataAdmin()
{
    ofstream writeData(dataFilePath);
    if (!writeData.is_open())
    {
        cerr << "cannot open file";
        return;
    }
    data["buses"] = buses;
    writeData << data.dump(4);
    writeData.close();
};

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

// for the input function
string User::inputFirstName()
{
    string fName;

    while (1)
    {
        cout << "\nEnter First Name \n> ";
        cin >> fName;
        if (isNameValid(fName, "")) // ref to valid.cpp
        {
            break;
        }
    }
    fName = toLowerInput(fName);
    fName = capName(fName);

    return fName;
}

string User::inputLastName()
{
    string lName;

    while (1)
    {
        cout << "\nEnter Last Name \n> ";
        cin >> lName;
        if (isNameValid(lName, ""))
        {
            break;
        }
    }
    lName = toLowerInput(lName);
    lName = capName(lName); // ref to valid.cpp

    return lName;
}

int User::inputAge()
{
    int age;

    while (true)
    {
        cout << "\nEnter Age \n> ";
        cin >> age;
        if (cin.fail())
        {
            clearInput();
            cout << "\nPlease enter again...\n\n";
            continue;
        }

        if (isAgeValid(age))
        {
            break;
        }
    }

    return age;
}

string User::inputEmail()
{
    int i = 0;
    string email;

    while (1)
    {
        if (i >= 2)
        {
            cout << "\nHint: log in instead\n";
        }
        cout << "\nEnter Email \n> ";
        cin >> email;
        email = toLowerInput(email);                            // ref to valid.cpp
        if (isEmailAvailable(email) /*&& isEmailValid(email)*/) // ref to valid.cpp [WHEN DONE CHANGE TO CHECK FOR VALIDITY]
        {
            break;
        }
        i++;
    }

    return email;
}

string User::inputPassword()
{
    string pass;

    while (1)
    {
        cout << "\nEnter Password \n> ";
        cin >> pass;
        if (isPasswordValid(pass))
        {
            break;
        }
    }
    return pass;
}

string User::confirmPassword(string pass) // password thats passed is passed as a hashed password
{
    string passCf;

    while (true)
    {
        cout << "\nEnter Password Again\n> ";
        cin >> passCf;
        if (isPasswordSame(pass, passCf)) // reference to validation.cpp
        {
            break;
        }
    }

    return passCf;
}

// input for addBus function
//  string User::inputBusType()
//  {
//      string busType;
//          cout<<"Enter bus type:"<<endl;
//          cin>>busType;

//     return busType;
// }

// int User::inputSeatCap()
// {
//     int seatcap;
//     const int MIN_CAPACITY = 8;
//     const int MAX_CAPACITY = 130;
//     while (1){
//         cout<<"Enter the bus seat capacity (from 8-130):"<<endl;
//         cin>>seatcap;
//         if (seatcap < MIN_CAPACITY || seatcap > MAX_CAPACITY){
//             cout<<"Invalid seat capacity! Please enter again.";
//             continue;
//         }
//         else{
//             break;
//         }
//     }
//     return seatcap;
// }

// End of helper methods for Reserve =============================================================

void User::viewBus()
{
    int option;
    cout << "Please choose the option\n";
    cout << "1. View All Buses.\n";
    cout << "2. View By Bus by ID.\n";
    cout << "Option> ";
    cin >> option;
    if (option == 1)
    {
        this->viewAllBus();
    }
    else if (option == 2)
    {
        this->viewBusbyID();
    }
    else
    {
        cout << "Please try again.";
    }
}
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