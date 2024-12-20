# nlohmann JSON Library

The **nlohmann JSON** library is a C++ library designed to simplify working with JSON data. It provides a user-friendly interface for parsing, serializing, and deserializing JSON objects, making it easy to interact with JSON in C++ applications.

## Key Features:

- **Parsing**: Read and parse JSON data from strings, files, or streams.
- **Serialization/Deserialization**: Convert C++ objects to JSON format and vice versa.
- **STL-like API**: Allows you to use JSON as if it were a standard C++ container (e.g., `std::map`, `std::vector`).
- **Header-only**: Can be used by simply including a single header file, no additional setup required.
- **Supports Modern C++**: Fully compatible with C++11 and later.

## Usage in Bus Management System:

In the bus management system, we can use the nlohmann JSON library to manage and store user data, booking information, and bus schedules in JSON format. For example, storing a new booking or retrieving bus schedules from a JSON file:

```cpp
ifstream readFile(dataFilePath);
if (!readFile.is_open())
{
    cerr << "\nError: cannot open" << dataFilePath;
}
json allData;
readFile >> allData;
readFile.close();

json newUser;
newUser["id"] = generateUserID();
newUser["name"]["firstName"] = fName;
newUser["name"]["lastName"] = lName;
newUser["age"] = age;
newUser["email"] = email;
newUser["password"] = passCf;
newUser["isAdmin"] = false;
newUser["resID"] = json::array();
allData["users"].push_back(newUser);

ofstream writeFile(dataFilePath);
if (!writeFile.is_open())
{
    cerr << "Error: cannot open file" << dataFilePath;
}
writeFile << allData.dump(4);
writeFile.close();
```
