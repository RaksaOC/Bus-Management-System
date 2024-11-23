#include <iostream>
#include <vector>
#include <string>

#include "../utils/Header-Files/System.hpp"

using namespace std;

// -----------------------------------------------------------------

// user.reserve // get the user thats reserving for easy operations , user.refund, user.view

int main()
{
    System sys;
    User user = sys.authenticateUser();
    user.selectService();
    return 0;
}
