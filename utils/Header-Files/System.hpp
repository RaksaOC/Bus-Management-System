#ifndef System_hpp
#define System_hpp

// -------------------------------------------------------

#include "User.hpp"

#include <iostream>
#include <vector>
using namespace std;
// -------------------------------------------------------

class System // responsivility: For adding and authenticating users
{
private:
    User user;
public:
    System(){};
    void addUser(string uID, string n, int a, string e, string pass)
    {
        user.setUserID(uID);
        user.setName(n);
        user.setAge(a);
        user.setEmail(e);
        user.setPassword(pass);
    }
    User getUser()
    {
        return user;
    }
    // bool logIn()
    // {
    //     string email;
    //     string password;

    //     cout << "Enter your email: ";
    //     cin >> email;
    //     // go check if valid email
    //     if (/* valid email*/ 1)
    //     {
    //         cout << "enter your Password: ";
    //         cin >> password;
    //         // go check if valid password
    //         if (1 /*valid password*/)
    //         {
    //             // return true
    //         }
    //         else
    //         {
    //             // return false;
    //         }
    //     }
    // }
    // bool signUp();
    // bool isUser()
    // {
    //     if (logIn() || signUp()) // log in returns true
    //     {
    //         // return true
    //     }
    // };
};

#endif