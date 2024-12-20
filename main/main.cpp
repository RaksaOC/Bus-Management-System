#include <iostream>
#include <vector>
#include <string>

#include "../utils/header/System.hpp"
#include "../utils/header/User.hpp"
using namespace std;

// -----------------------------------------------------------------

int main()
{
    System sys;
    User *user = sys.authenticateUser();
    user->checkUserType();
    return 0;
}
