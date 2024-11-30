# **System Class Documentation**

## **Overview**

The **System** class handles user authentication, including login and signup processes. It interacts with a JSON file to securely store and retrieve user data, managing user details such as name, age, email, password, and admin status. The class returns a `User` object for further operations.

---

## **Flow**

| **Step**               | **Description**                                                                                           |
| ---------------------- | --------------------------------------------------------------------------------------------------------- |
| **1. Authentication**  | `authenticateUser()` prompts the user to choose between login or signup.                                  |
| **2. Login Process**   | `logIn()` verifies the email and password, retrieves user details, and returns a `User` object.           |
| **3. Signup Process**  | `signUp()` collects user details, validates inputs, saves new user data, and creates a `User` object.     |
| **4. Helper Methods**  | Validates inputs (e.g., name, email), hashes passwords, and assists in retrieving or saving user details. |
| **5. Data Management** | Reads from and writes to a JSON file (`Data.json`) for user data storage and retrieval.                   |

---

## **Public Methods**

| **Method**                 | **Description**                                                            | **Returns**                         |
| -------------------------- | -------------------------------------------------------------------------- | ----------------------------------- |
| `User* authenticateUser()` | Prompts the user to log in or sign up. Routes to the appropriate method.   | A pointer to the authenticated user |
| `int logInOrSignUp()`      | Displays a menu for login or signup options.                               | `1` for login or `2` for signup     |
| `User* logIn()`            | Handles login by validating credentials and retrieving user details.       | A pointer to the `User` object      |
| `User* signUp()`           | Handles signup by validating inputs, saving data, and creating a new user. | A pointer to the new `User` object  |

---

## **Private Helper Methods (Signup)**

| **Method**                 | **Description**                                                                  | **Returns**         |
| -------------------------- | -------------------------------------------------------------------------------- | ------------------- |
| `void loadUser()`          | Loads user data from `Data.json` into memory.                                    | N/A                 |
| `string inputFirstName()`  | Prompts and validates the user's first name.                                     | A valid first name  |
| `string inputLastName()`   | Prompts and validates the user's last name.                                      | A valid last name   |
| `int inputAge()`           | Prompts and validates the user's age.                                            | A valid age         |
| `string inputEmail()`      | Prompts and validates the user's email address.                                  | A valid email       |
| `string inputPassword()`   | Prompts and validates the user's password for strength.                          | A valid password    |
| `string confirmPassword()` | Prompts for password confirmation and ensures it matches the original password.  | The hashed password |
| `string generateUserID()`  | Generates a unique user ID based on the existing number of users in `Data.json`. | A new user ID       |

---

## **Private Helper Methods (Login)**

| **Method**                  | **Description**                                                    | **Returns**                   |
| --------------------------- | ------------------------------------------------------------------ | ----------------------------- |
| `vector<string> getResID()` | Retrieves the reservation IDs associated with the given email.     | A vector of reservation IDs   |
| `bool getAdminStatus()`     | Checks whether the user with the given email has admin privileges. | `true` if admin, else `false` |
| `string getID()`            | Retrieves the user ID associated with the given email.             | A user ID                     |
| `string getEmail()`         | Retrieves the email associated with the logged-in user.            | A user email                  |
| `string getPassword()`      | Retrieves the hashed password associated with the given email.     | The hashed password           |
| `int getAge()`              | Retrieves the age of the user with the given email.                | The user's age                |
| `string getFirstName()`     | Retrieves the first name of the user with the given email.         | The user's first name         |
| `string getLastName()`      | Retrieves the last name of the user with the given email.          | The user's last name          |

---

## **Data Handling**

The **System** class interacts with a JSON file (`Data.json`) located in `../utils/Database/` for user data storage and retrieval.

### **User Data Format (JSON)**

```json
{
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

- **json.hpp**: Used for parsing and writing JSON data to and from the file.
- **sha1.hpp**: Provides functionality to hash the password using SHA1.
- **validation.cpp**: Contains functions for input validation such as name and email format checks.

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
