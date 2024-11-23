#include <iostream>
#include <fstream> // For file I/O
using namespace std;

#include "../utils/Libs/json.hpp"
using json = nlohmann::json;

int main()
{
    // Define the file path
    std::string filePath = "../utils/Database/UserData.json";

    // --- Writing to JSON File ---
    try
    {
        // Create a JSON object
        json userData = {
            {"users", {{{"name", "Alice"}, {"userID", "12345"}, {"bookingHistory", {{{"reservationID", "r001"}, {"busID", "bus123"}, {"seats", {"1A", "1B"}}, {"status", "confirmed"}}}}}, {{"name", "Bob"}, {"userID", "67890"}, {"bookingHistory", {}}}}}};

        // Write JSON object to file
        std::ofstream outFile(filePath);
        if (!outFile.is_open())
        {
            throw std::ios_base::failure("Failed to open file for writing.");
        }
        outFile << userData.dump(4); // Pretty-print with an indent of 4 spaces
        outFile.close();
        std::cout << "JSON data written to " << filePath << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error writing to file: " << e.what() << std::endl;
        return 1;
    }

    // --- Reading from JSON File ---
    try
    {
        // Read the JSON file
        std::ifstream inFile(filePath);
        if (!inFile.is_open())
        {
            throw std::ios_base::failure("Failed to open file for reading.");
        }

        // Parse the JSON data
        json readData;
        inFile >> readData;
        inFile.close();

        // Access and print some data
        for (const auto &user : readData["users"])
        {
            std::cout << "Name: " << user["name"] << "\n"
                      << "User ID: " << user["userID"] << "\n"
                      << "Booking History: " << user["bookingHistory"] << "\n\n";
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error reading from file: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}