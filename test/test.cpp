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
int main(){
    // //read file
    // json data;
    // ifstream read("./userTest.json");
    // if(!read.is_open()){
    //     std::cout<<"no file found";
    // }
    // read >> data;
    // User user;
    // std::vector<int> busNum;
    // for(int i=1;i<=25;i++){
    //     busNum.push_back(i);
    // }
    // // User use
    // // user.reserve();
}
