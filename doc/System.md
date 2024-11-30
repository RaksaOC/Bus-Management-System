# System Class Documentation 

## Overview 

The System class is responsible for handling user authentication, including both login and signup processes. It interacts with a JSON file to store and retrieve user data, managing user details such as name, age, email, password, and admin status and then return a user object for further user operations.

## Flow

1. **User Authentication Process:**
   - The `authenticateUser` method initiates the authentication process, presenting the user with an option to either **log in** or **sign up**.
   
2. **Login Flow:**
   - If the user chooses to log in, the `logIn` method is triggered.
   - The system prompts for the user’s **email** and **password**.
   - The email is verified, and the corresponding password is checked against stored data. 
   - If valid, a `User` object is created and returned.

3. **Signup Flow:**
   - If the user chooses to sign up, the `signUp` method is triggered.
   - The system prompts for **first name**, **last name**, **age**, **email**, and **password**.
   - The system validates the input and ensures the email is not already registered.
   - A new user ID is generated, and the user's data is added to the stored JSON file.
   - A `User` object is created and returned.

4. **Helper Methods:**
   - Various helper methods are used for input validation, such as `inputFirstName`, `inputLastName`, `inputAge`, etc.
   - Passwords are hashed using SHA1 before storage.
   - Helper methods also assist in retrieving user data like email, password, and user status for login.

5. **User Data Management:**
   - User data is stored in a JSON file (`Data.json`) and is loaded or updated during the login and signup processes.

## Public Methods

**User* authenticateUser()**
Prompts the user to choose between logging in or signing up. Depending on the choice, it directs the user to either the login or signup method.
**Returns**: A User object representing the authenticated user (admin or normalUser).

**int logInOrSignUp()**
Displays a menu to the user prompting them to choose between logging in or signing up.
**Returns**: The user's choice, either 1 (Login) or 2 (Signup).

**User* logIn()**
Handles the login process. It validates the user's email and password, then retrieves the user details from the JSON file and returns a User object.
**Returns**: A pointer to the User object if authentication is successful.

**User* signUp()**
Handles the signup process. It collects user details, validates the inputs, generates a new user ID, hashes the password, and saves the new user information into the JSON file.
**Returns**: A pointer to the newly created User object.

## Private Helper Methods (for Sign Up)

**void loadUser()**
Loads the user data from the Data.json file into the userData member variable.

**string inputFirstName(), string inputLastName()**
Prompts the user to enter their first and last name. The input is validated for proper formatting. 
**Returns**: a string first name or last name.

**int inputAge()**
Prompts the user to enter their age. The input is validated to ensure it is a valid age.
**Returns**: age

**string inputEmail()**
Prompts the user to enter their email address. The email is validated for format and availability.
**Returns**: a string email.

**string inputPassword()**
Prompts the user to enter their password. The password is validated for strength.
**Returns**: a string password for further confirmation.

**string confirmPassword(string pass)**
Prompts the user to confirm their password. Ensures that the entered confirmation matches the original password.
**Returns**: a **hashed** password.

**string generateUserID()**
Generates a new user ID based on the number of existing users in the Data.json file.
**Returns**: a new ID string for a new User (last user id++)

## Private Helper Methods (for Log In)

**vector<string> getResID(string em)**
Retrieves the reservation IDs associated with a given email address. (Currently a placeholder to be modified.)
**Returns**: a vector or linked list of resIDs.

**bool getAdminStatus(string em)**
Checks if the user with the specified email has admin privileges.
**Returns**: a bool true or false.

**string getID(string em), string getEmail(), string getPassword(string email), int getAge(string em), string getFirstName(string em), string getLastName(string em)**
These methods retrieve specific user details such as ID, email, password, age, first name, and last name from the JSON data.

## Data Handling

The System class interacts with a JSON file (Data.json) located in ../utils/Database/ to store and retrieve user information.

**User Data Format (JSON):**

```json
{
    "buses": [
        /*[Bus Data]*/
    ]
    "users": [
        {
            "id": "U000001",
            "name": {
                "firstName": "John",
                "lastName": "Doe"
            },
            "age": 30,
            "email": "john.doe@example.com",
            "password": "hashedPassword",
            "isAdmin": false,
            "resID": []
        }
    ]
}
```

## File & Dependencies

The header file includes the following dependencies:

- **User.hpp**: Contains the definition of the User class.
- **menu.hpp**: Contains menu-related functionality, including displaying the login or signup menu.
- **validation.cpp**: Provides functions for validating user input (such as names, passwords, and email).
- **json.hpp**: Used for handling JSON data, specifically for reading and writing user information to/from a file.
- **sha1.hpp**: Provides functionality for hashing passwords.
- **Standard Libraries**: Includes essential C++ standard libraries such as `<iostream>, <stdexcept>, and <fstream>` for file handling and user input/output.

## Dependencies

**json.hpp**: Used for parsing and writing JSON data to and from the file.
**sha1.hpp**: Provides functionality to hash the password using SHA1.
**validation.cpp**: Contains functions for input validation such as name and email format checks.

## Notes

- The login process hashes the entered password and compares it with the stored hashed password for authentication.
- The signup process includes user input validation and generates a unique user ID for each new user.

## Example Usage

```cpp
System system;
User *authenticatedUser = system.authenticateUser();

// If user is logged in or signed up successfully
authenticatedUser.operation();
```