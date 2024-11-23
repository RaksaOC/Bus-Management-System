# Bus Management System

## Overview

This project is a simple bus management system that allows users to reserve, refund, and view their bookings. The system involves multiple classes such as **System**, **User**, **Bus**, and **Route** to manage users, buses, routes, and reservations. 

It also utilizes the **nlohmann/json** library for handling JSON data.

## How It Works

The system operates as follows:

1. When the program starts, the user is prompted to either log in or sign up.
2. After authentication, the user can:
   - **Reserve** a seat by selecting from available buses.
   - **Refund** a previously booked reservation.
   - **View their booking history** to see past reservations.

## Class Structure

The system is designed with the following classes:

- **System Class**: Responsible for adding and authenticating users.
- **User Class**: Manages user operations like reserving seats, refunding, and viewing booking history.
- **Bus Class**: Represents bus details such as ID, type, seat count, price, and availability.
- **Route Class**: Handles route details, such as origin and destination, and can be extended for future functionalities.

### Class Hierarchy

```
System
│
├── User
│   ├── Reserve
│   ├── Refund
│   └── ViewHistory
│
├── Bus
│   ├── Route
│   │   └── setRoute
│   └── Waitlist (Future)
│       ├── enQueue
│       └── deQueue
```
###  File Structure
```
Bus Mangement System/
    ├── main/
        ├──main.cpp             # Entry point of the application
    ├── utils/
        ├── Header-Files/
        │   ├── System.hpp       # Header for the System class
        │   ├── User.hpp         # Header for the User class
        │   ├── Bus.hpp          # Header for the Bus class
        │   ├── Route.hpp        # Header for the Route class
        │   ├── Ticket.hpp       # Header for the optional Ticket class
        │   ├── menu.cpp         # Contains decision-making menu and ASCII art 
        ├── Libs/
        │   ├── json.hpp         # nlohmann JSON library
        ├── Database/
        │   ├── BusData.json     # contains data for Bus
        │   ├── UserData.json     # contains data for User
    ├── test/
        test.cpp             # For testing things
    ├── README.md            # Project documentation 
```
## Steps to Compile and Run

1. Clone this repository:
   
   `git clone https://github.com/RaksaOC/Bus-Management-System.git`

2. Make sure you have the necessary dependencies installed. For this project, you will need:
   - A C++ compiler (e.g., `g++`)

3. Compile the code:
   `g++ -std=c++11 main -o main.cpp `

4. Run the program:
   `./main`

5. Follow the on-screen prompts to interact with the system (user login, bus reservation, etc.).

**Happy Coding!**

