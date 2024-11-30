#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cctype>
#include <string>
#include "../Libs/json.hpp"

#define dataFile "../utils/Database/Data.json"

using namespace std;
using json = nlohmann::json;

// VALIDATION FUNCTIONS FOR SIGN UP ====================================

bool isNameValid(string fName, string lName)
{
    string fullName = fName + lName;
    for (int i = 0; i < fullName.size() - 1; i++)
    {
        if (isdigit(fullName[i]) || ispunct(fullName[i]))
        {
            cout << "\nError: Name cannot contain numbers or punctuations\n";
            return false;
        }
    }
    return true;
}

bool isAgeValid(int age)
{
    if (age < 13 && age > 110)
    {
        if (age < 13)
        {
            cout << "\nError: User must be older than 13 years old\n";
        }
        else if(age > 110){
            cout << "\nError: User is too old\n";
        }
        return false;
    }
    return true;
}

bool isEmailAvailable(string email)
{
    ifstream readData(dataFile);
    if (!readData.is_open())
    {
        cerr << "\nError: Failed to open file, Path: " << dataFile << " \n";
        return false;
    }

    // Parse the JSON data
    json allData;
    readData >> allData;
    readData.close();

    // Iterate through the users to check for email
    for (const auto &user : allData["users"])
    {
        if (user.contains("email") && user["email"] == email)
        {
            cout << "\nError: Email is taken\n";
            return false;
        }
    }

    // Email is available
    return true;
}

bool isEmailValid(string email)
{
    for (int i = 0; i < email.size(); i++)
    {
        if (email[i] == '@')
        {
            string emailEndCheck = email.substr(i, email.size());
            if (emailEndCheck == "@gmail.com")
            {
                return true;
            }
            else
            {
                cout << "\nError: Email is invalid\n";
                return false;
            }
        }
    }
    return false;
}

bool isPasswordValid(string pass)
{
    // check for atleast 6 char long [Implement more requirements in the future]
    if (pass.size() < 6)
    {
        cout << "\nError: Password must be longer than 6 characters\n";
        return false;
    }
    return true;
}

bool isPasswordSame(string pass1, string pass2)
{
    if (pass1 != pass2)
    {
        cout << "\nError: Re-Entered password is not the same\n";
        return false;
    }
    return true;
}

string toLowerInput(string i)
{
    string loweredInput;
    for (char c : i)
    {
        loweredInput += tolower(c);
    }
    return loweredInput;
}

string capName(string n)
{
    n[0] = toupper(n[0]);
    return n;
}

// VALIDATION FUNCTIONS FOR LOG IN ==================================================
