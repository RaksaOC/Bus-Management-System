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

// add bus 

set busType;

set departureTime;

generate busID;

    int baseBusID = "B0000"
    int nextID = buses.size() + 1;
    string nextID_string = toString(nextID);

    int start = baseBusID.size() - nexID_string.size()

    int j = 0;
    for(i = start; i < baseBusID.size(); i++){
        baseBusID[i] = nexID_string[j];
        j++;
    }

// example: baseRes = "B0000" and the next resID is "120" so start from baseRes[2] 2 = baseRes(5 char) - nexIDString(3 char)
    
set route: from, to

set seatCap, seatLeft = 0, seatPrice;

// based on seatCap create that amount of seats in the "seats" object
json seats; // this is an array
json newSeat;
newSeat["seatNum"] = 0;
newSeat["status"] = "available";
for(int i = 0; i < seatCap; i++){
    newSeat["seatNum"] = i + 1;
    seats.push_back(newSeat);
    // this means that for every iteration append a new seat obj to the "seats" array by incrementing the seatNumber by 1 each time
}
