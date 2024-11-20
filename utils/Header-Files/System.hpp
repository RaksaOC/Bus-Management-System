#ifndef System_hpp
#define System_hpp

#include "User.hpp"
#include "menu.cpp"

#include <iostream>
using namespace std;

// -------------------------------------------------------

class System // Responsibility: Handles user authentication (login/signup)
{
private:
    int logInOrSignUp(); 
    void logIn(); 
    void signUp(); 

public:
    // Default constructor
    System() = default;

    // Initiates the user authentication process
    void authenticateUser()
    {
        switch (logInOrSignUp())
        {
        case 1:
            logIn();
            break;
        case 2:
            signUp();
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            authenticateUser(); // Recursive call for invalid input
            break;
        }
    }
};

// Prompts the user to choose between login and signup
int System::logInOrSignUp()
{
    // [TO DO]
    // LOGIC:
    // 1. Display a menu with options: 
    //    "1. Log In" 
    //    "2. Sign Up"
    // 2. Get the user's choice and return it
    // 3. Validate the input to ensure it is either 1 or 2
    // 4. Return the choice
}

// Handles the login process
void System::logIn()
{
    // [TO DO]
    // LOGIC:
    // 1. Prompt the user to enter their credentials (username/password)
    // 2. Validate the credentials against a stored user database/file
    // 3. If valid, construct a User object with their data
    // 4. If invalid, prompt the user again or provide an option to exit
}

// Handles the signup process
void System::signUp()
{
    // [TO DO]
    // LOGIC:
    // 1. Prompt the user for required details (e.g., username, password, etc.)
    // 2. Validate the input (e.g., check for duplicate usernames)
    // 3. Save the user information to the database/file
    // 4. Confirm successful signup and allow login or go to the service selection
}

#endif
