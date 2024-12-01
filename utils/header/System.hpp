#ifndef System_hpp
#define System_hpp

#include "User.hpp"
#include "menu.hpp"
#include "validation.cpp"
#include "../libs/json.hpp"
#include "../libs/sha1.hpp"

#include <iostream>
#include <stdexcept>

#define dataFilePath "../utils/database/Data.json"
using namespace std;
using namespace sha1;
using json = nlohmann::json;

// -------------------------------------------------------

class System // Responsibility: Handles user authentication (login/signup)
{
private:
    /*User Data JSON object to use for helper method*/
    /********************************************/
    // Core function
    /********************************************/
    int logInOrSignUp();
    User *logIn();
    User *signUp();
    bool isAdmin();
    /********************************************/
    // Helper Functions for sign up
    /********************************************/
    void loadUser();
    string inputFirstName();
    string inputLastName();
    int inputAge();
    string inputEmail();
    string inputPassword();
    string confirmPassword(string);
    string generateUserID();
    /********************************************/
    // Helper Functions for log in
    /********************************************/
    string getID(string);
    int getAge(string);
    string getFirstName(string);
    string getLastName(string);
    bool getAdminStatus(string);
    vector<string> getResID(string);
    string getEmail();
    string getPassword(string);
    /********************************************/
    /*User Data JSON object to use for helper methods*/
    json userData;
    /********************************************/

public:
    System() {}               // Default-construct `User` object
    User *authenticateUser(); // Initiates the user authentication process (return a user obj)
};

// MAIN METHOD ===============================================================================
User *System::authenticateUser() // Prompts the user to choose between login and signup
{
    // LOGIC : navigate user to whether the login page or the signup page
    printBusManagementSystem(); // ref to menu.hpp
    int choice = this->logInOrSignUp();
    loadUser();
    switch (choice)
    {
    case 1:
        return this->logIn();
        break;
    case 2:
        return this->signUp();
        break;
    default:
        // will never get here
        break;
    }
    User *user;
    return user;
}

//  CORE METHODS ==============================================================================

int System::logInOrSignUp()
{
    int choice = logInOrSignUpMenu(); // pre-made menu in menu.cpp
    return choice;
}

// Handles the signup process
User *System::signUp()
{
    /*Get attributes*/
    string fName = inputFirstName();
    string lName = inputLastName();
    int age = inputAge();
    string email = inputEmail();
    string pass = inputPassword();
    string passCf = confirmPassword(pass);
    passCf = hashPassword(passCf);

    ifstream readFile(dataFilePath);
    if (!readFile.is_open())
    {
        cerr << "\nError: cannot open" << dataFilePath;
    }
    json allData;
    readFile >> allData;
    readFile.close();

    json newUser;
    newUser["id"] = generateUserID();
    newUser["name"]["firstName"] = fName;
    newUser["name"]["lastName"] = lName;
    newUser["age"] = age;
    newUser["email"] = email;
    newUser["password"] = passCf;
    newUser["isAdmin"] = false;
    newUser["resID"] = json::array();
    allData["users"].push_back(newUser);

    ofstream writeFile(dataFilePath);
    if (!writeFile.is_open())
    {
        cerr << "Error: cannot open file" << dataFilePath;
    }
    writeFile << allData.dump(4);
    writeFile.close();

    vector<string> emptyResID;
    User *user = new User(generateUserID(), fName, lName, fName + " " + lName, age, email, pass, false, emptyResID);
    return user;
}

// Handles the login process
User *System::logIn()
{
    /*Get attributes*/
    string email = getEmail();
    string password = getPassword(email);
    string fName = getFirstName(email);
    string lName = getLastName(email);
    int age = getAge(email);
    string ID = getID(email);
    bool adminStatus = getAdminStatus(email);
    vector<string> resID = getResID(email);

    User *user = new User(ID, fName, lName, fName + " " + lName, age, email, password, adminStatus, resID);
    return user;
}

// HELPER METHODS ===============================================================================

// HELPER FUNCTIONS FOR SIGN UP ===============================================================================

void System::loadUser()
{
    json allData;
    ifstream readData(dataFilePath);
    if (!readData.is_open())
    {
        cerr << "\nError: cannot open " << dataFilePath;
        return;
    }
    readData >> allData;
    json userData = allData["users"];

    this->userData = userData;
}

string System::inputFirstName()
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

string System::inputLastName()
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

int System::inputAge()
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

string System::inputEmail()
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

string System::inputPassword()
{
    string pass;

    while (1)
    {
        cout << "Enter Password \n> ";
        cin >> pass;
        // UNCOMMENT THIS WHEN DONE
        // if (isPasswordValid(pass))
        // {
        //     break;
        // }
        break; // [THIS LINE TO CHANGE]
    }
    return pass;
}

string System::confirmPassword(string pass) // password thats passed is passed as a hashed password
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

string System::generateUserID()
{
    int lastID = userData.size();
    string fullID = "U000000";
    string lastID_string = to_string(lastID);
    int start = fullID.size() - lastID_string.size();

    for (int i = 0; i < lastID_string.size(); i++)
    {
        fullID[start + i] = lastID_string[i];
    }

    return fullID;
}

// HELPER FUNCTIONS FOR LOG IN ===============================================================================

vector<string> System::getResID(string em)
{
    // [TO CHANGE]
    vector<string> str;
    return str;
}

bool System::getAdminStatus(string em)
{
    bool isAdmin = false;

    for (const auto &user : userData)
    {
        if (user["email"] == em)
        {
            isAdmin = user["isAdmin"];
        }
    }

    return isAdmin;
}

string System::getID(string em)
{
    string ID;

    for (const auto &user : userData)
    {
        if (user["email"] == em)
        {
            ID = user["id"];
        }
    }

    return ID;
}

string System::getEmail()
{
    string email;
    bool foundEmail = false;

    while (1)
    {
        cout << "Enter Email\n> ";
        cin >> email;
        email = toLowerInput(email); // reference to validation.cpp

        for (const auto &user : userData)
        {
            if (user["email"] == email)
            {
                foundEmail = true;
                break;
            }
        }
        if (foundEmail)
        {
            return email;
        }
        else
        {
            cout << "\nError: Email not found\n\n";
        }
    }

    return "";
}

string System::getPassword(string email)
{
    string pass;
    bool foundPass = false; // load the user obj

    while (1)
    {
        cout << "Enter password\n> ";
        cin >> pass;
        pass = hashPassword(pass);
        for (const auto &user : userData)
        {
            if (user["email"] == email && user["password"] == pass)
            {
                foundPass = true;
                break;
            }
        }
        if (foundPass)
        {
            return pass;
        }
        else
        {
            cout << "\nError: Incorrect Password\n\n";
        }
    }

    return "";
}

int System::getAge(string em)
{
    int age;

    for (const auto &user : userData)
    {
        if (user["email"] == em)
        {
            age = user["age"];
        }
    }

    return age;
};

string System::getFirstName(string em)
{
    json name;

    for (const auto &user : userData)
    {
        if (user["email"] == em)
        {
            name = user["name"];
        }
    }

    return name["firstName"];
}

string System::getLastName(string em)
{
    json name;

    for (const auto &user : userData)
    {
        if (user["email"] == em)
        {
            name = user["name"];
        }
    }

    return name["lastName"];
}

bool System::isAdmin()
{
    for (const auto &u : userData)
    {
        if (u["isAdmin"] == true)
        {
            return true;
        }
    }

    return false;
}

#endif
