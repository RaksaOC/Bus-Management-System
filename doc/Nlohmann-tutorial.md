
# Tutorial: Using the nlohmann/json Library in C++ For Bus Management System

The **nlohmann/json** library is a powerful and easy-to-use C++ library for working with JSON data and it allows you to change, add, and grab data. For this tutorial, we’ll focus on the usage of this library in our **Bus Management System**.

 --- 
 
## Table of Contents


1. [Getting Started](#getting-started)
2. [Working with Arrays](#working-with-arrays-(basics-reading-data))
3. [Use Case Scenarios](#use-case-scenarios)

---

 
## Getting Started

### Setting Up

The header is already included:

```cpp
	#include <nlohmann/json.hpp>
	using  json  =  nlohmann::json;
```
### Understand Json Object Initialization

```cpp
	int main(){
		json jsonObject; // means that this objects can store things from the json file and understands itself
	}
```
### Reading files & Storing into a json object

```cpp
	int main(){
		json jsonObject; 
		ofstream read("filePath");
		read >> jsonObject; // put whatever was in the json file and put it into the json object
	}
```

## Working With Arrays (Basics - Reading Data)

### We have a Json file that looks like this: 

```json
"users": [
	{
		"age": 18,
		"email": "dev",
		"id": "U000000",
		"isAdmin": true,
		"name": {
			"firstName": "Dev",
			"lastName": "Dev"
		},
	"password": "34c6fceca75e456f25e7e99531e2425c6c1de443",
	"resID": []
	},
	{
		"age": 18,
		"email": "me",
		"id": "U000001",
		"isAdmin": false,
		"name": {
			"firstName": "kdmv",
			"lastName": "kmjkj"
		},
	"password": "34c6fceca75e4s9df7swre99531e2425c6c1de433",
	"resID": [R00001,R00002,R00103]
	},
]
```
**Example1**: I want to find get the email of the **first** user.

Here's the code snippet of using the array in the json object to access that email.

```cpp
	int main(){
		json data; 
		ifstream read("filePath");
		read >> data; // put whatever was in the json file and put it into the json object
		string email = 	data["users"][0]["email"]; // get the users object and then the first element of that object and then the email object of that element
	}
```

**Example 2**: Find the User Who Is Not an Admin and print their info

Here's the code snippet:

```cpp
`int main() {
    json data;
    ifstream read("filePath");
    read >> data;

    for (const auto& user : data["users"]) {
        if (!user["isAdmin"]) {
            std::cout << user.dump(4) << std::endl;
        }
    }
}
```
**Example 3**: Display Reservation IDs of a Specific User

```cpp
`int main() {
    json data;
    ifstream read("filePath");
    read >> data;

    std::string userID = "U000001";
    for (const auto& user : data["users"]) {
        if (user["id"] == userID) {
            for (const auto& res : user["resID"]) {
                std::cout << res << " ";
            }
        }
    }
}
```
**Example 4**: Creating a new json Object that only contains the object that we want.

In our `data.json` file we have 3 high level objects: `buses`, `users` and `reservations`. So for best practice, we should make a json object that only contain one of the three high level objects.

In the user-authentication feature, we only work with the `users` class so its good to just get a user json object to avoid confusion and complexity when accessing a part of the user's data.

Code Snippet:

```cpp
int main(){
	json allData; // assume we read and this stores all!!!! the stuff in the files
	
	// Now to get only a specific part of all the data
	
	// 1. get only the users obj
	json usersData = allData["users"];
	// 2. get only the buses obj
	json busData = allData["buses"];
	// 3. get only the reservation obj
	json resData = allData["reservations"];
	return 0;
}
```


## Use Case Scenarios (Reading/Validating & Writing)

### Using the same user json object:

```json
"users": [
	{
		"age": 18,
		"email": "dev",
		"id": "U000000",
		"isAdmin": true,
		"name": {
			"firstName": "Dev",
			"lastName": "Dev"
		},
	"password": "34c6fceca75e456f25e7e99531e2425c6c1de443",
	"resID": []
	},
	{
		"age": 18,
		"email": "me",
		"id": "U000001",
		"isAdmin": false,
		"name": {
			"firstName": "kdmv",
			"lastName": "kmjkj"
		},
	"password": "34c6fceca75e4s9df7swre99531e2425c6c1de433",
	"resID": [R00001,R00002,R00103]
	},
]
```

**Example**: Signing Up a User (Will work with the user object)

When a user signs up, their data can be stored as follows:

```cpp
	//to get inputs
	string fName = inputFirstName();
    string lName = inputLastName();
    int age = inputAge();
    string email = inputEmail();
    string pass = inputPassword();
    string passCf = confirmPassword(pass);
    passCf = hashPassword(passCf);
    
    // store all inputs to this object
	json newUser;
    newUser["id"] = generateUserID();
    newUser["name"]["firstName"] = fName;
    newUser["name"]["lastName"] = lName;
    newUser["age"] = age;
    newUser["email"] = email;
    newUser["password"] = passCf;
    newUser["isAdmin"] = false;
    newUser["resID"] = json::array(); // empty array
    allData["users"].push_back(newUser); // append to the user array
	ofstream writeFile(dataFilePath);
    if (!writeFile.is_open())
    {
        cerr << "Error: cannot open file" << dataFilePath;
    }
    
    // write the object back to the file
    writeFile << allData.dump(4);
    writeFile.close();
```

**Example**: Logging in a User (Will work with the user object)

When a user logs in we need to check for the email, and then with that email go see the person's passwords, names... 
and see if it checks out.
```cpp
/*Get attributes*/

	string  email  =  getEmail();
	string  password  =  getPassword(email);
	string  fName  =  getFirstName(email);
	string  lName  =  getLastName(email);
	int  age  =  getAge(email);
	string  ID  =  getID(email);
	bool  adminStatus  =  getAdminStatus(email);
	vector<string>  resID  =  getResID(email);

// generally the functions' definitions looks like this(get a thing so we call that thing "thingToCheckFor")

	string thingToCheckFor;
	json data;
	ifstream openFile("filePath");
	openFile >> data; // data has all data
	json userData = data["users]; // this means that go and then only get the users part to store
	while(1){
		cout << "Enter thing: ";
		cin >> thingToCheckFor;
		for(const auto &user : userData){ // means for each user in userData
			if(user["thing"] == thingToCheckFor) return true;
			else{return false};
		} 
	}

```

### Example 3: **Check if an Email Exists**

Verify if a specific email already exists in the system.

 ```cpp
bool isEmailAvailable(string emailToCheck) {
	json data;
    std::ifstream read("filePath");
    read >> data;
  
    for (const auto &user : data["users"]) {
        if (user["email"] == emailToCheck) {
            return true; // Email found
        }
    }
    return false; // Email not found
}

int main() {
    std::string emailToCheck;
    std::cout << "Enter email: ";
    std::cin >> emailToCheck;

    if (isEmailAvailable(emailToCheck, data)) {
        std::cout << "Proceed to services...\n";
    } else {
        std::cout << "Email not found...\n";
    }

    return 0;
}
```

---