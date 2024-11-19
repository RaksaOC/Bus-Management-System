#include <iostream>
#include <vector>
#include <string>

#include "../utils/Header-Files/System.hpp"
#include "../utils/Header-Files/menu.cpp"

using namespace std;

// -----------------------------------------------------------------

// user.reserve // get the user thats reserving for easy operations , user.refund, user.view

int main()
{
    System sys;
    sys.addUser("011010", "Raksa", 18, "OCraksa@gmail.com", "123"); // this function should be used within the class maybe
    User currentUser = sys.getUser();
    printBusManagementSystem();
    int service = startMenu();
    switch (service)
    {
    case 1:
        currentUser.reserve();
    case 2:
        
    default:
        break;
    }
    return 0;
}
