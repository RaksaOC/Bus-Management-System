#ifndef User_hpp
#define User_hpp

#include <iostream>
#include <vector>
#include "Bus.hpp"
using namespace std;

// -------------------------------------------------------------------

class User
{
private:
    string userID;
    string name;
    int age;
    string email;
    string password;
    vector<string> resID; // Stores reservation IDs

    // Helper Methods
    void printSeats();       // Helper function to display seat layout
    void loadReservations(); // Loads previous reservations for refund/view history

public:
    User() = default; // Default constructor
    // Constructor to initialize user data after authentication
    User(string UID, string n, int a, string em, string pswd)
    {
        userID = UID;
        name = n;
        age = a;
        email = em;
        password = pswd;
    }

    // Set and Get methods
    void setResID(string r) { resID.push_back(r); }
    string getUID() { return userID; }
    string getName() { return name; }
    int getAge() { return age; }
    string getEmail() { return email; }
    string getPassword() { return password; }

    // Core User Methods
    int selectService();
    void reserve();     // Method for reserving a bus ticket
    void refund();      // Method for refunding a reservation
    void viewHistory(); // Method for viewing reservation history
};

// int User::selectService()
// {
//     int choice = serviceMenu();
//     switch (choice)
//     {
//     case 1:
//         reserve();
//         break;
//     case 2:
//         refund();
//         break;
//     case 3:
//         viewHistory();
//         break;
//     default:
//         break;
//     }
// }

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

#endif
