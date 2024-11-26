#include <iostream>
#include <fstream>
using namespace std;

#include "../utils/libs/json.hpp"

using json = nlohmann::json;
int main()
{
    string email;
    string pass;
    cout << "Email: ";
    cin >> email;
    cout << "Password: ";
    cin >> pass;
    ofstream outFile("./test.json");
    json userData = {
        {"Email", email},
        {"Password", pass}};
    outFile << userData.dump(4);
    outFile.close();
    // read the file
    std::ifstream inFile("./test.json");

    // Step 2: Parse JSON data from the file
    json userDataRead;
    // puts whatever thats in the file into the obj
    inFile >> userDataRead;

    // Step 3: Close the file
    inFile.close();
    std::cout << "Email: " << userDataRead["Email"] << std::endl;
    std::cout << "Password: " << userDataRead["Password"] << std::endl;
}
