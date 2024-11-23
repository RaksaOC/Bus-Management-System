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
    User logIn();
    User signUp();
    User user;

public:
    System() : user(User()) {} // Default-construct `User` object

    // Initiates the user authentication process
    User authenticateUser()
    {
        printBusManagementSystem();
        int choice = this->logInOrSignUp();
        switch (choice)
        {
        case 1:
            logIn();
            break;
        case 2:
            signUp();
            break;
        default:
            break;
        }
        // logic of filling user attributes goes here
        return user;
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
    int choice = logInOrSignUpMenu(); // pre-made menu in menu.cpp
    return choice;
}

// Handles the login process
User System::logIn()
{
    // [TO DO]
    // LOGIC:
    // 1. Prompt the user to enter their credentials (username/password)
    // 2. Validate the credentials against a stored user database/file
    // 3. If valid, construct a User object with their data
    // 4. If invalid, prompt the user again or provide an option to exit
    return user;
}

// Handles the signup process
User System::signUp()
{
    // [TO DO]
    // LOGIC:
    // 1. Prompt the user for required details (e.g., username, password, etc.)
    // 2. Validate the input (e.g., check for duplicate usernames)
    // 3. Save the user information to the database/file
    // 4. Confirm successful signup and allow login or go to the service selection
    return user;
}

#endif
