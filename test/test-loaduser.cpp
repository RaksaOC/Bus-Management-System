#include <iostream>
#include <fstream>
#include "../utils/header/User.hpp"

int main() {
    User user;

    user.setDataFilePath("data.json");

    
    user.getAllUsers();

    return 0;
}