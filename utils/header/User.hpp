#ifndef User_hpp
#define User_hpp

#include <iostream>
#include <vector>
#include <limits>
#include <stack>
#include "Bus.hpp"
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

    //function for supporting the add-admin function
    string inputFirstName();
    string inputLastName();
    int inputAge();
    string inputEmail();
    string inputPassword();
    string confirmPassword(string);
    string generateUserID();


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

    // view history helper methods
    void printHistory(vector<int>, string);

    // After working with the bus object(reserve seat....)
    void generateResID(int, json, vector<int>, int);
    void generateTicket(int);
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
    void reserve();     // Method for reserving a bus ticket
    void refund();      // Method for refunding a reservation
    void viewHistory(); // Method for viewing reservation history

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
        int choice = serviceMenu();
        switch (choice)
        {
        case 1:
            this->reserve();
            break;
        case 2:
            this->refund();
            break;
        case 3:
            this->viewHistory();
            break;
        default:
            break;
        }
    }
}

// Method for reserving a bus ticket
void User::reserve()
{
    loadData();
    destinationMenu();
    string from = inputFrom();
    string to = inputTo(from);
    vector<int> busIdx = showAvailableBuses(from, to);

    Bus bus = selectBus(busIdx);
    bus.printBusInfo();
    bus.showSeatLayout();

    json chosenSeat;
    json seatsOfBus;
    vector<int> seatsChangedArr;
    chosenSeat["seatNum"] = -1;
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
    generateTicket(chosenSeat["seatNum"]);
    printThanks();
}

// // Method for refunding a reservation
void User::refund()
{

    // [TO DO]
    // LOGIC:
    // 1. Show a list of previous reservations associated with the user.
    // 2. Prompt user to select a reservation to refund.
    // 3. Prompt for confirmation (Are you sure you want to refund?).
    // 4. Delete the selected reservationID from the user’s list.
    // 5. Update data files to reflect the refund.

    // [Note] : Similar to viewHistory, but includes operations to update data.
}

void User::viewHistory()
{
    loadData();
    stack<string> resIDStack;

    // Push all reservation IDs into the stack
    for (auto &res : this->resID)
    {
        resIDStack.push(res);
    }

    // Process each reservation ID from the stack
    cout << "\nORDERED BY LATEST\n\n";
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
                    printHistory(seatNums, busID);
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
                    seatNum.push_back(res["seatNumber"]);
                    printHistory(seatNum, busID);
                }
            }
        }

        resIDStack.pop();
    }
}

void User::printHistory(vector<int> seatNums, string bID)
{
    json busInfo;
    for (const auto &bus : buses)
    {
        if (bus["id"] == bID)
            busInfo = bus;
    }
    
    cout << "\n*****************************************************************" << endl;
    cout << "* Type: " << busInfo["busType"] << "\t\t" << endl;
    cout << "* Bus ID: " << busInfo["id"] << "\t\t" << endl;
    cout << "* Departure time: " << busInfo["departureTime"] << "\t\t" << endl;
    cout << "* From: " << busInfo["route"]["from"] << "\t\t" << endl;
    cout << "* To: " << busInfo["route"]["to"] << "\t\t" << endl;
    cout << "* Seat numbers: ";
    for (int s : seatNums)
    {
        cout << s << " ";
    }
    cout << "\n*****************************************************************\n"
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
    if (!readFile.is_open()){
        cerr <<"\n Error cannot open:"<<dataFile;
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
void User::addBus() {
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
    for(int i = start; i < baseID.size(); i++){
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
void User::deleteBus() {
    //delete bus 
    string busID;
    cout<<"PLease input bus id you want to delete"<<endl;
    cin>>busID;

    bool isFound = false;
    char confirm;
    loadData();
    for (auto it = buses.begin(); it != buses.end(); ++it) {
        if ((*it)["id"] == busID) {
            isFound = true;

            
            cout << "Bus found:" << endl;
            cout << endl << endl << "----------------------Bus-----------------------" << endl << endl;
            cout << "ID: " << (*it)["id"] << endl;
            cout << "Bus Type: " << (*it)["busType"] << endl;
            cout << "DepartureTime: " << (*it)["departureTime"] << endl;
            cout << "route: " << (*it)["route"]["from"]<<"to " <<(*it)["route"]["to"]<< endl;
            cout << "Seat Capacity: " << (*it)["seatCap"] << endl;
            cout << "Seat left: " << (*it)["seatLeft"] << endl;
            cout << "Seat price: " << (*it)["seatPrice"] <<"$"<< endl;
            cout << endl << "__________________________________________________" << endl << endl;

            if((*it)["seatLeft"] != (*it)["seatCap"]){
                cout <<endl<< "Cannot delete bus " << busID << " because it have active reservations." << endl;
                break;
            }

            cout << "Are you sure you want to delete this user with ID " << userID << " (y/n)? ";
            cin >> confirm;

            if (confirm =='y' || confirm == 'Y'){
                buses.erase(it); 
                cout << "Bus deleted successfully." << endl;

                
                data["buses"] = buses;

                
                ofstream writeData(dataFilePath);
                if (!writeData.is_open()) {
                    cerr << "Error: Unable to save changes to file." << endl;
                } else {
                    writeData << data.dump(4);  
                    writeData.close();
                    cout << "Changes saved to file." << endl;
                }
            }else {
                
                cout << "Bus deletion canceled." << endl;
            }
            break;
        }

    }
    if (!isFound){
        cout<<"Bus does not exist"<<endl;
    }

}

void User::getAllUsers() {
    int option;
    string userID;
    bool isFound = false;
    loadData();

    // Option selection loop
    while (true) {
        cout << "Please input option (1/2):" << endl;
        cout << "1/ View one user by input their ID." << endl;
        cout << "2/ View all the existing users." << endl;
        cout << "Input here: ";
        cin >> option;

        // Check if the option is valid
        if (option < 1 || option > 2) {
            cout << "Invalid option, please try again." << endl;
            continue;
        }
        break;  // Exit the loop if option is valid
    }

    // Option 1: View a user by ID
    if (option == 1) {
        while (true) {
            cout << "Please input user ID: ";
            cin >> userID;

            // Validate userID length and format
            if (userID.length() != 7) {
                cerr << "Invalid length: " << userID << endl;
                continue;
            }
            if (userID[0] != 'U') {
                cerr << "Invalid format: Does not start with 'U'" << endl;
                continue;
            }

            //for search for the user
            isFound = false;
            for (auto it = users.begin(); it != users.end(); ++it) {
                if ((*it)["id"] == userID) {
                    isFound = true;
                    // Print user information if found
                    cout << "\n\nUser found:\n" << endl;
                    cout << endl << endl << "----------------------Users-----------------------" << endl << endl;
                    cout << "ID: " << (*it)["id"] << endl;
                    cout << "Name: " << (*it)["name"]["firstName"] << " " << (*it)["name"]["lastName"] << endl;
                    cout << "Age: " << (*it)["age"] << endl;
                    cout << "Email: " << (*it)["email"] << endl;
                    cout << "Is Admin: " << (*it)["isAdmin"] << endl;
                    cout << "Password: " << (*it)["password"] << endl;
                    cout << "Reservation: " << (*it)["resID"] << endl;
                    cout << endl << "__________________________________________________" << endl << endl;
                    break;  // Break loop after finding the user
                }
            }

            if (!isFound) {
                cout << "User does not exist." << endl<<"Please try again"<<endl;
                continue;
            }
            break;
        }
    } 
    // Option 2: View all users
    else {
        cout << endl << endl << "----------------------All Users-------------------------" << endl << endl;
        for (const auto& user : users) {
            cout << "ID: " << user["id"] << endl;
            cout << "Name: " << user["name"]["firstName"] << " " << user["name"]["lastName"] << endl;
            cout << "Age: " << user["age"] << endl;
            cout << "Email: " << user["email"] << endl;
            cout << "Is Admin: " << user["isAdmin"] << endl;
            cout << "Password: " << user["password"] << endl;
            cout << "Reservation: " << user["resID"] << endl;
            cout << endl << "__________________________________________________" << endl << endl;
        }
    }
}


void User::deleteUser() {
    string userID;
    cout << "Please input the user ID you want to delete: " << endl;
    cin >> userID;

    
    loadData();

    bool isFound = false;
    char confirm;

    
    for (auto it = users.begin(); it != users.end(); ++it) {
        if ((*it)["id"] == userID) {
            isFound = true;

            
            cout << "User found:" << endl;
            cout << "ID: " << (*it)["id"] << endl;
            cout << "Name: " << (*it)["name"]["firstName"] << " " << (*it)["name"]["lastName"] << endl;
            cout << "Age: " << (*it)["age"] << endl;
            cout << "Email: " << (*it)["email"] << endl;
            cout << "Is Admin: " << (*it)["isAdmin"] << endl;
            cout << "Password: " << (*it)["password"] << endl;
            cout << "Reservation: " << (*it)["resID"] << endl;

            if(!(*it)["resID"].empty()){
                cout << "Cannot delete user " << userID << " because they have active reservations." << endl;
                break;
            }

            
            cout << "Are you sure you want to delete this user with ID " << userID << " (y/n)? ";
            cin >> confirm;

            if (confirm =='y' || confirm == 'Y') {
                
                users.erase(it); 
                cout << "User deleted successfully." << endl;

                
                data["users"] = users;

                
                ofstream writeData(dataFilePath);
                if (!writeData.is_open()) {
                    cerr << "Error: Unable to save changes to file." << endl;
                } else {
                    writeData << data.dump(4);  
                    writeData.close();
                    cout << "Changes saved to file." << endl;
                }
            } else {
                
                cout << "User deletion canceled." << endl;
            }
            break;
        }
    }

    if (!isFound) {
        cout << "User does not exist." << endl;
    }
}

void User::viewAllBus() {
    cout<<endl<<endl<<"----------------------All Buses-------------------------"<<endl<<endl;
    loadData();
    for (const auto& bus : buses) {
        cout << "Bus Type: " <<bus["busType"] << endl;
        cout << "ID: " <<bus["id"] << endl;
        cout << "Departure Time: " <<bus["departureTime"] << endl;
        cout << "Route: "<<bus["route"]["from"] <<" to "<< bus["route"]["to"] << endl;
        cout << "Seat Cap: " << bus["seatCap"] << endl;
        cout << "Seat Left: " << bus["seatLeft"] << endl;
        cout << "Seat Price: "<< bus["seatPrice"] << endl;
        cout<<endl<<endl<<"__________________________________________________"<<endl<<endl;;
    }
}
void User::viewBusbyID() {
     string busID;
    cout<<"Please Input the Bus you want to find: ";
    cin>>busID;
    bool isFound = false;
    char confirm;
    loadData();
    for (auto it = buses.begin(); it != buses.end(); ++it) {
        if ((*it)["id"] == busID) {
            isFound = true; 
            cout << "Bus found:" << endl;
            cout << endl << endl << "----------------------Bus-----------------------" << endl << endl;
            cout << "ID: " << (*it)["id"] << endl;
            cout << "Bus Type: " << (*it)["busType"] << endl;
            cout << "DepartureTime: " << (*it)["departureTime"] << endl;
            cout << "route: " << (*it)["route"]["from"]<<"to " <<(*it)["route"]["to"]<< endl;
            cout << "Seat Capacity: " << (*it)["seatCap"] << endl;
            cout << "Seat left: " << (*it)["seatLeft"] << endl;
            cout << "Seat price: " << (*it)["seatPrice"] << endl;
            cout << endl << "__________________________________________________" << endl << endl;
            break;   
        }
    }
    if (!isFound) {
        cout << "ID is invalid." << endl;
    }
}


// helper methods for Reserve ============================================================

void User::loadData()
{
    ifstream readData(dataFilePath);
    if (!readData.is_open())
    {
        cerr << "Couldn't open file" << endl;
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
    cout << "\t\t\tAVAILABLE ROUTES\n\n";
    cout << "*****************************************************************" << endl;
    for (const auto &route : routes)
    {
        for (const auto &to : route["to"])
        {
            cout << "*\t" << route["from"] << "\t -------> \t" << to << "\t\t*" << endl;
        }
    }
    cout << "*****************************************************************" << endl;
}

string User::inputFrom()
{
    string from;
    while (1)
    {
        cout << "From\n> ";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the buffer
        getline(cin, from);
        if (isFromValid(from, routes))
        {
            break;
        }
        else
        {
            cout << "\nInvalid origin\n";
        }
    }
    return from;
}

string User::inputTo(string from)
{
    string to;
    while (1)
    {
        cout << "To\n> ";
        getline(cin, to);
        if (isToValid(from, to, routes))
        {
            break;
        }
        else
        {
            cout << "\nInvalid destination\n";
        }
    }
    return to;
}
vector<int> User::showAvailableBuses(string f, string t)
{
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
        cout << "Bus " << ":\n\n";
        cout << "*******************************************" << endl;
        cout << "* ID: " << bus["id"] << endl;
        cout << "* Type: " << bus["busType"] << endl;
        cout << "* Departure: " << bus["departureTime"] << endl;
        cout << "* Number of Seats: " << bus["seatCap"] << endl;
        cout << "* Remaining Seats: " << bus["seatLeft"] << endl;
        cout << "* Price: $" << bus["seatPrice"] << endl;
        cout << "*******************************************" << endl;
        return i; // Return the index of the correct bus
    }
    return -1; // Return -1 if the bus doesn't match
}

Bus User::selectBus(vector<int> busIdxArr)
{
    int choice;
    cout << "Select a bus \n> ";
    cin >> choice;
    choice = choice - 1;
    int busIndex = busIdxArr[choice];

    busToModify = buses[busIndex];

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

        this->resID.push_back(baseResID);
        reservations["bulkReservations"].push_back(newResObj);
    }
}
void User::showQRCode()
{
    cout << "\n\nProceeding to payment... Please scan the QR code.\n";
    cout << "Your QR code will open now...\n";
    system("open ../../qr.jpg");
    cout << "After scanning, press Enter to confirm payment.\n";
    cin.get();
}

void User::generateTicket(int seatNum)
{
    cout << "\n\n\t\t\t\tTICKET \n\n";
    cout << "*******************************************" << endl;
    cout << "* Reservation ID: " << modifiedUser["resID"][modifiedUser["resID"].size() - 1] << endl;
    cout << "* Bus ID: " << busToModify["id"] << endl;
    cout << "* Bus Type: " << busToModify["busType"] << endl;
    cout << "* Departure Time: " << busToModify["departureTime"] << endl;

    // Print route details
    cout << "* From: " << busToModify["route"]["from"] << endl;
    cout << "* To: " << busToModify["route"]["to"] << endl;

    // Print seat details
    cout << "* Seat Number: " << seatNum << endl;
    cout << "* Total Price: $" << busToModify["seatPrice"] << endl;
    cout << "*******************************************" << endl;
    cout << "\n\n\n";
}

void User::storeDataAdmin(){
    ofstream writeData(dataFilePath);
    if(!writeData.is_open()){
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
        cerr << "Couldn't open file";
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

//for the input function
string User::inputFirstName()
{
    string fName;

    while (1)
    {
        cout << "Enter First Name \n> ";
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
        cout << "Enter Last Name \n> ";
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
        cout << "Enter Age \n> ";
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
        cout << "Enter Email \n> ";
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
        cout << "Enter Password \n> ";
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
        cout << "Enter Password Again\n> ";
        cin >> passCf;
        if (isPasswordSame(pass, passCf)) // reference to validation.cpp
        {
            break;
        }
    }

    return passCf;
}

//input for addBus function
// string User::inputBusType()
// {
//     string busType;
//         cout<<"Enter bus type:"<<endl;
//         cin>>busType;

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


void User::viewBus(){
    int option;
    cout << "Please choose the option\n";
    cout << "1. View All Buses.\n";
    cout << "2. View By Bus by ID.\n";
    cout << "Option> ";
    cin >> option;
    if (option == 1) {
        this->viewAllBus();
    } else if (option == 2) {
        this->viewBusbyID();
    } else {
        cout << "Please try again.";
    }   
}
#endif