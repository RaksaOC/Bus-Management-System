# User Class Documentation

This documentation provides an overview of the `User` class, its attributes, and methods. The `User` class represents a user of the bus reservation system, handling both normal users and admins. The class supports functionality such as managing reservations, handling user details, and enabling admin-level actions.

### **Header Inclusion**
- `iostream`: For input/output operations.
- `vector`: For handling lists (e.g., reservation IDs).
- `Bus.hpp`: Represents buses (assumed for bus-related operations).
- `menu.hpp`: Provides menus for admin and user options.

## **Attributes**
The `User` class has the following attributes:

### **Private Attributes**
| Attribute     | Type            | Description                                   |
|---------------|-----------------|-----------------------------------------------|
| `userID`      | `string`        | Unique identifier for the user.              |
| `name`        | `string`        | Full name of the user.                       |
| `lastName`    | `string`        | Last name of the user.                       |
| `firstName`   | `string`        | First name of the user.                      |
| `age`         | `int`           | Age of the user.                             |
| `email`       | `string`        | User's email address.                        |
| `password`    | `string`        | User's password (encrypted storage assumed). |
| `isAdmin`     | `bool`          | Indicates if the user has admin privileges.  |
| `resID`       | `vector<string>`| List of reservation IDs associated with the user. |

### **Private Helper Methods**
| Method               | Description                                          |
|----------------------|------------------------------------------------------|
| `printSeats()`       | Displays seat layout for reservation. **To be documented.** |
| `loadReservations()` | Loads and displays user's previous reservations. **To be documented.** |

---

## **Constructors**
| Constructor                         | Description                                                                      |
|-------------------------------------|----------------------------------------------------------------------------------|
| `User()`                            | Default constructor.                                                            |
| `User(string UID, string fn, string ln, string n, int a, string em, string pswd, bool aS, vector<string> rID)` | Initializes a user with given details.                                          |

---

## **Public Methods**
The following methods provide functionality for the `User` class:

### **Getters**
| Method             | Return Type | Description                                   |
|--------------------|-------------|-----------------------------------------------|
| `getUID()`         | `string`    | Returns the user's unique ID.                |
| `getName()`        | `string`    | Returns the user's full name.                |
| `getFirstName()`   | `string`    | Returns the user's first name.               |
| `getLastName()`    | `string`    | Returns the user's last name.                |
| `getAge()`         | `int`       | Returns the user's age.                      |
| `getEmail()`       | `string`    | Returns the user's email address.            |
| `getPassword()`    | `string`    | Returns the user's password.                 |
| `getAdminStatus()` | `bool`      | Returns whether the user has admin privileges.|

### **Setters**
| Method              | Parameters     | Description                                  |
|---------------------|----------------|----------------------------------------------|
| `setResID(string r)`| `string r`     | Adds a reservation ID to the user's list.    |

### **Core User Methods**
| Method             | Description                                                                                   |
|--------------------|-----------------------------------------------------------------------------------------------|
| `checkUserType()`  | Redirects the user to either admin or normal user menus based on `isAdmin`.                   |
| `reserve()`        | Handles the process of reserving a bus ticket. **To be documented.**                         |
| `refund()`         | Handles the process of refunding a reservation. **To be documented.**                        |
| `viewHistory()`    | Displays the user's reservation history. **To be documented.**                                |

### **Core Admin Methods**
| Method                 | Description                                          |
|------------------------|------------------------------------------------------|
| `addAdmin()`           | Adds a new admin user. **To be documented.**         |
| `addBus()`             | Adds a new bus to the system. **To be documented.**  |
| `changeBusSettings()`  | Modifies bus settings. **To be documented.**         |
| `getAllUsers()`        | Retrieves and displays all users. **To be documented.** |

### **Helper Functions**
| Method         | Description                                                                                  |
|----------------|----------------------------------------------------------------------------------------------|
| `printUser()`  | Displays the user's details.                                                                |
| `printSeats()` | Displays seat layout for reservations. **To be documented.**                                |
| `loadReservations()` | Loads and displays reservations for refund/view history. **To be documented.**         |

---

## **Functionality Summary**

1. **User Management:**
   - Handles user authentication and admin identification.
   - Supports reservation and history viewing for users.
   
2. **Admin Management:**
   - Admin-specific functionality for adding buses, admins, and modifying bus settings.

3. **Reservation Handling:**
   - Provides methods for reserving seats, processing refunds, and managing user reservations.

4. **Future Features:**
   - Complete implementations for reservations, refunds, and admin actions.

---

## **TO DO**
- Implement missing methods:
  - `reserve()`
  - `refund()`
  - `viewHistory()`
  - Admin-related methods: `addAdmin()`, `addBus()`, `changeBusSettings()`, `getAllUsers()`.
- Document helper functions (`printSeats()` and `loadReservations()`).

---

### **Example Usage**
```cpp
User user("U001", "John", "Doe", "John Doe", 25, "john@example.com", "password123", false, {});
user.printUser();
if (user.getAdminStatus()) {
    user.checkUserType(); // Redirect to admin actions
} else {
    user.reserve(); // Start reservation process
}
```