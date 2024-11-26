#ifndef System_hpp
#define System_hpp

#include "User.hpp"
#include "menu.cpp"
#include "../libs/json.hpp"

#include <iostream>
using namespace std;
using json = nlohmann::json;

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
    User authenticateUser();
    // Initiates the user authentication process
};

// Prompts the user to choose between login and signup
User System::authenticateUser()
{
    // LOGIC : navigate user to wither the login page or the signup page

    printBusManagementSystem();
    int choice = this->logInOrSignUp();
    switch (choice)
    {
    case 1:
        return logIn();
        break;
    case 2:
        return signUp();
        break;
    default:
        break;
    }
    return user;
}

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
    string email;
    string pass;
    cout << "\t\t\t\t LOGGING IN\n";
    cout << "Email: ";
    cin >> email;
    cout << "Password: ";
    cin >> pass;
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
    string email;
    string pass;
    string passCf;
    int age;
    string fName;
    string lName;

    while (true)
    {
        cout << "\t\t\t\t SIGN UP\n";
        cout << "Enter First Name\n> ";
        cin >> fName;
        cout << "Enter Last Name\n> ";
        cin >> lName;
        while (1)
        {
            cout << "Enter Age\n> ";
            cin >> age;
            if (age > 3 && age < 120)
            {
                break;
            }
            else
            {
                cout << "\nInvalid...\n";
            }
        }
        while (1)
        {
            cout << "Enter Email\n> ";
            cin >> email;
            ifstream checkUser("../utils/Database/UserData.json");
            json userData;
            checkUser >> userData;
            checkUser.close();
            if (userData["Email"] != email)
            {
                break;
            }
            else
            {
                cout << "\nEmail is taken...\n";
            }
        }

        cout << "Enter password\n >";
        cin >> pass;
        cout << "Enter password again\n >";
        cin >> passCf;
    }

    ofstream writeUser("../utils/Database/UserData.json");
    if (!writeUser.is_open())
    {
        std::cerr << "Failed to open the file for writing!" << std::endl;
        return user;
    }
    json userData = {
        {"Name", name},
        {"Age", age},
        {"Email", email},
        {"Password", pass},
    };
    writeUser << userData.dump(4);
    writeUser.close();
    return user;
}

#endif
