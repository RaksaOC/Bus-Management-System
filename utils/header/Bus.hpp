#ifndef Bus_hpp
#define Bus_hpp

#include <iostream>
#include <vector>
#include <fstream>
#include "Route.hpp"
#include "../libs/json.hpp"

#define dataFilePath "../utils/database/Data.json"
using json = nlohmann::json;
using namespace std;

class Bus
{
private:
    string busID;           // Unique ID for the bus
    string busType;         // Type of bus (e.g., luxury, economy)
    int seatCap;            // Total seat capacity
    int seatPrice;          // Price per seat
    vector<int> seatStatus; // Seat status (e.g., 0 = available, 1 = reserved)
    json seats;
    vector <string> resIDofUserArr;
    json reservation;
public:
    // Constructor
    Bus(string ID, string type, int cap, int price, json s)
    {
        busID = ID;
        busType = type;
        seatCap = cap;
        seatPrice = price;
        seatStatus = vector<int>(cap, 0); // Initialize all seats as available
        // [TO DO] Load additional bus data if needed
        seats=s;
    }

    // Core Bus Methods
    void showSeatLayout(const json& seats);                            // Displays seat layout of the bus
    void reserveSeat(int seat);                       // Reserves a single seat
    bool reserveSeats(vector<int> seats);             // Reserves multiple seats
    bool isSeatAvailable(int seat);                   // Checks if a specific seat is available
    void setRoute(string origin, string destination); // Sets a route for the bus
    // helper methods
    void loadReservation();
    void getResIDOfUser(vector <string>);
    string generateResID();
    void storeToFile();
};

void Bus::showSeatLayout(const json& seats)
{
    vector <int> seatNumArr;
    vector <string> seatStatusArr;
    for(json seat : seats){
        seatStatusArr.push_back(seat["status"]);
        seatNumArr.push_back(seat["seatNum"]);
    }
    int z=0;
    int sizeOfSeat;
    if(seatStatus.size()%4==0){
        sizeOfSeat=seatStatus.size()/4;
    }else{
        sizeOfSeat=seatStatus.size()/4+1;
    }
    for(int i=0; i<sizeOfSeat;i++){
        for(int j=0;j<2;j++){
            for(int k=0;k<2;k++){
                if(seatStatusArr.at(z)!="reserved"){
                    cout<<seatNumArr.at(z)<<" ";
                    z++;
                }else{
                    cout<<"X"<<" ";
                    z++;
                }
            }
            cout<<"\t";
        }
    }
    // int z=0;
    // for(int i){
    //     for(int i=0; i<2;i++){
    //         if(seatStatusArr!="reserved"){
    //             if(seatNumArr.at(z)%4==0){
    //                 cout<<seatNumArr.at(z)<<endl;
    //             }
                
    //         }
    //     }
    // }
    // [TO DO]
    // - Iterate through `seatStatus` vector
    // - Display seat numbers and their availability (e.g., 0 = available, 1 = reserved)
}

// Reserves a single seat
void Bus::reserveSeat(int seatNum)
{
    for(auto &seat : seats){
        if (seat["seatNum"] == seatNum)
        {
            seat["status"] = "reserved";
        }
    }
    resIDofUserArr.push_back(generateResID());
    return;
}

// Checks if a specific seat is available
bool Bus::isSeatAvailable(int seat)
{
    for(const auto& seat:seats ){
        if(seat["seatNum"]==seat && seat["status"]=="available"){
            return true;
        }
    }
    // [TO DO]
    // - Verify if `seat` index is within bounds of `seatStatus`
    // - Return true if `seatStatus[seat] == 0` (available), otherwise false
    return false;
}

void Bus::loadReservation(){
    ifstream readReservation(dataFilePath);
    if(!readReservation.is_open()){
        cerr << "Could'nt load file";
        return;
    }
    readReservation >> this->reservation;
}

string Bus::generateResID(){
    int lastResID = reservation.size();
    string baseResID = "R000000";
    lastResID++;
    string lastResID_string = to_string(lastResID);
    int start = baseResID.size() - lastResID_string.size();
    int j = 0;
    for (int i = start; i < baseResID.size(); i++)
    {
        baseResID[i] = lastResID_string[j];
        j++;
    }
}

void Bus::getResIDOfUser(vector <string> resID){
    this->resIDofUserArr = resID;
}

void Bus::storeToFile(){
    ifstream readAllData(dataFilePath);
    if (!readAllData.is_open())
    {
        cerr << "Cant find file" << endl;
        return;
    }
    json allData;
    readAllData >> allData;
    json userData = allData["users"];
    json busData = allData["buses"];
    json resData = allData["reservations"];
    
}

#endif
