#ifndef User_hpp
#define User_hpp

#include <fstream>
#include <iostream>
#include <vector>
#include "Bus.hpp"
#include "menu.hpp"
#include <limits>
#define dataFilePath "../utils/database/Data.json"
using namespace std;

// -------------------------------------------------------------------

class User
{
private:
    string userID;
    string name;
    string lastName;
    string firstName;
    int age;
    string email;
    string password;
    bool isAdmin;
    vector<string> resID; // Stores reservation IDs
    json allData;
    json userData;
    json busData;
    json resData;

    // Helper Methods
    void printSeats();       // Helper function to display seat layout
    void loadReservationsData(); // Loads previous reservations for refund/view history
    void loadAllData();
    void loadBusData();
    void loadUserData();
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
    void setResID(string r) { resID.push_back(r); }

    void checkUserType(); // check and redirect the user to be admin or normal user
    // Core User Methods
    void reserve();     // Method for reserving a bus ticket
    void refund();      // Method for refunding a reservation
    void viewHistory(); // Method for viewing reservation history
    // Core Admin Methods
    void addAdmin();
    void addBus();
    void changeBusSettings();
    void getAllUsers();

    // Helper Functions
    void printUser();
};
// Method for reserving a bus ticket
void busReservationMenu(){
    
}
void User::reserve()
{   string busOrigin;
    string busDestination;
    string busID;
    string busType;
    int busCap;
    int busPrice;
    json seats;
    string originDestinationChoice[2];
    bool validOriginDestination=false;
    do{
        cout<<"Available Routes:\n\t1.Phnom Penh-Siemp Reap\n\t2.Phnom Penh-Kompot\n";
        cout<<"Your origin: ";
        cin>> originDestinationChoice[0];
        cout<<"Desired destination: ";
        cin>> originDestinationChoice[1];
        for(const auto &bus : busData){
            if (bus["route"]["from"] == originDestinationChoice[0] && bus["route"]["to"] == originDestinationChoice[1])
            {
                cout << "*****************************\n";
                cout << bus["busType"]<<endl;
                cout<<bus["seatCap"]<<endl;
                cout<<bus["route"]["from"]<< " - "<<bus["route"]["from"]<<endl; 
                cout<<bus["seatPrice"]<<endl;
                validOriginDestination=true;
                busOrigin=bus["route"]["from"];
                busDestination=bus["route"]["to"];
                busID = bus["id"];
                busType = bus["busType"];
                busCap = bus["seatCap"];
                busPrice = bus["seatPrice"];
                seats = bus["seats"];
                break;
            }
            if(!validOriginDestination){
                cout<<"Your input is invalid!!! Please try again"<<endl;
            }
        }
    }while(!validOriginDestination);
    Bus bus(busID, busType, busCap, busPrice, seats);
    bus.showSeatLayout(seats);
    int choosingSeatChoice;
    do{
        cout<<"Choose one of the available seats: "<<endl;
        cin>>choosingSeatChoice;
    }while(!bus.isSeatAvailable(choosingSeatChoice));
    bus.reserveSeat(choosingSeatChoice);
    cout<<"-------------------------------------------------------\n";
    cout<<"| Bus Type: "<< busType<<endl;
    cout<<"| Route: "<< busOrigin<<" - "<<busDestination<<endl;
    cout<<"| Name: "<< name<<endl;
    cout<<"| Seat's Number: "<< choosingSeatChoice<<endl;
    cout<<"| ID"<< userID<<endl;
    cout<<"| Price"<< busPrice<<endl;
    cout<<"-------------------------------------------------------\n";
    // [TO DO]
    // LOGIC:
    // 1. Prompt user for From, To, Date/Day (delegate to helper method).
    // 2. Search for buses based on user input (delegate to bus search logic).
    // 3. Display available buses and prompt user to select (delegate to helper method).
    // 4. Show bus seat layout (delegate to helper method to display seats).
    // 5. Ask for single or bulk booking (delegate to helper method).
    // 6. Collect seat numbers for reservation (delegate to helper method for input).
    // 7. Confirm the reservation and finalize (delegate to helper method to process the booking).
    // 8. Generate reservationID and associate with the user (delegate to helper method).
    // 9. Print ticket (delegate to ticket generation logic) name email resID busType date.

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



// Method for refunding a reservation
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

// Method for viewing reservation history
void User::viewHistory()
{
    // [TO DO]
    // LOGIC:
    // 1. Retrieve reservationIDs made by the user.
    // 2. Find detailed information about each reservation.
    // 3. Display the reservation details and allow user to return to the main menu.

    // [Note] : Need to consider how to retrieve detailed information based on reservation ID.
}

// Helper Methods (Private Section)

// Function to display seat layout for reservation
void User::printSeats()
{
    // [TO DO]
    // LOGIC:
    // - Display bus seat layout for the user to choose seats
    // - Indicate which seats are available/occupied
}



void User::addAdmin()
{
    // [TO DO] Define the functionality to add an admin
}

void User::addBus()
{
    // [TO DO] Define the functionality to add a bus
}

void User::changeBusSettings()
{
    // [TO DO] Define the functionality to change bus settings
}

void User::getAllUsers()
{
    // [TO DO] Define the functionality to get all users
}

// LOADING FUNCTIONS ==========================
void User::loadAllData(){
    ifstream readAll(dataFilePath);
    json allDt;
    readAll >> allDt;
    this->allData = allDt;
}

void User::loadUserData(){
    this->userData = this->allData["users"];
}
    

void User::loadBusData(){
    this->busData = this->allData["buses"];
}
void User::loadReservationsData(){
    this->resData = this->allData["reservations"];
}
#endif
