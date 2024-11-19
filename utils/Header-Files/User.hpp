#ifndef User_hpp
#define User_hpp

#include <iostream>
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
public:
    // Set and Get methods
    User(){};
    void setUserID(string uID)
    {
        userID = uID;
    }
    void setName(string n)
    {
        name = n;
    }
    void setAge(int a)
    {
        age = a;
    }
    void setEmail(string e)
    {
        email = e;
    }
    void setPassword(string pass)
    {
        password = pass;
    }
    string getUID()
    {
        return userID;
    }
    string getName()
    {
        return name;
    }
    int getAge()
    {
        return age;
    }
    string getEmail()
    {
        return email;
    }
    string getPassword()
    {
        return password;
    }
    // main Methods of user
    void reserve();
};

void User::reserve(){
    Bus stdBus;
    Bus luxBus;
    Bus dbDeckBus;
}

#endif