#include <iostream>
#include <vector>
#include <string>

#include "../utils/header/System.hpp"
#include "../utils/header/User.hpp"
using namespace std;

// -----------------------------------------------------------------

// user.reserve // get the user thats reserving for easy operations , user.refund, user.view

int main()
{
    // User user;
    // user.changeBusSettings();
    System sys;
    User *user = sys.authenticateUser();
    user->checkUserType();

    
    return 0;
}
