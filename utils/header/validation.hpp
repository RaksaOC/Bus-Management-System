#ifndef valid_hpp
#define valid_hpp

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cctype>
#include <string>
#include "../libs/json.hpp"

#define dataFile "../utils/database/Data.json"

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
            cout << invalidNameFormatMessage;
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
            cout << tooYoungMessage;
        }
        else if (age > 110)
        {
            cout << tooOldMessage;
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
        cerr <<  invalidFilePath + dataFile + '\n';
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
            cout << takenEmail;
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
                cout << invalidEmailFormatMessage;
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
        cout << invalidPasswordMessage;
        return false;
    }
    return true;
}

bool isPasswordSame(string pass1, string pass2)
{
    if (pass1 != pass2)
    {
        cout << "\n[⚠] \033[31mError: Re-Entered password is not the same\033[0m\n\n";
        return false;
    }
    return true;
}

// Formating functions

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

// VALIDATION FUNCTIONS FOR RESERVE ==================================================

bool isFromValid(string f, const json &routes)
{
    for (const auto &route : routes)
    {
        if (route["from"] == f)
        {
            return true;
        }
    }
    return false;
}
bool isToValid(string f, string t, const json &routes)
{
    for (const auto &route : routes)
    {
        if (route["from"] == f)
        {
            for (const auto &to : route["to"])
            {
                if (to == t)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool isResIDBulk(string r)
{
    if (r[0] == 'R' && r[1] == 'B')
    {
        return true;
    }
    return false;
}

#endif