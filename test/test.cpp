#include <iostream>
#include <fstream>
using namespace std;

#include "../utils/libs/json.hpp"
#include "../utils/Libs/sha1.hpp"
#include "../utils/header/User.hpp"

using json = nlohmann::json;
// int main()
// {
//     string email;
//     string pass;
//     cout << "Email: ";
//     cin >> email;
//     cout << "Password: ";
//     cin >> pass;
//     ofstream outFile("./test.json");
//     json userData = {
//         {"Email", email},
//         {"Password", pass}};
//     outFile << userData.dump(4);
//     outFile.close();
//     // read the file
//     std::ifstream inFile("./test.json");

//     // Step 2: Parse JSON data from the file
//     json userDataRead;
//     // puts whatever thats in the file into the obj
//     inFile >> userDataRead;

//     // Step 3: Close the file
//     inFile.close();
//     std::cout << "Email: " << userDataRead["Email"] << std::endl;
//     std::cout << "Password: " << userDataRead["Password"] << std::endl;
// }

std::string hashPassword(const std::string& password) {
    sha1::SHA1 sha1;
    sha1.processBytes(password.data(), password.size()); // Process the input password

    // Get the resulting digest (which is an array of 5 uint32_t values)
    sha1::SHA1::digest32_t digest;
    sha1.getDigest(digest);  // Get the 160-bit SHA1 hash (5 uint32_t values)

    // Convert the 5 uint32_t values into a hex string
    std::stringstream ss;
    for (int i = 0; i < 5; ++i) {
        ss << std::setw(8) << std::setfill('0') << std::hex << digest[i];
    }

    return ss.str();
}

int main(){
    string pass = "MYPASS";
    string hashedPass = hashPassword(pass);
    cout << "Nomal pass: ";
    cout << pass << endl;
    cout << "Hashed pass: ";
    cout << hashedPass << endl;;

}
