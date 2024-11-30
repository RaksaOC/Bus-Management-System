#ifndef User_hpp
#define User_hpp

#include <iostream>
#include <vector>
#include "Bus.hpp"
#include "menu.hpp"
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

    // Helper Methods
    void printSeats();       // Helper function to display seat layout
    void loadReservations(); // Loads previous reservations for refund/view history

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

// Method for reserving a bus ticket
void User::reserve()
{
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
    // 9. Print ticket (delegate to ticket generation logic).
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

// Function to load and display user’s reservations (used in refund and viewHistory)
void User::loadReservations()
{
    // [TO DO]
    // LOGIC:
    // - Load and display all reservationIDs associated with the user
    // - This can be called by refund and viewHistory methods to fetch user's past reservations.
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

#endif
