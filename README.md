# Bus Management System

## Overview

The **Bus Management System** is a command-line application built with C++ designed to handle bus bookings, refunds, and waitlist management. It offers seamless user interactions for making reservations, handling refunds, and efficiently managing bus occupancy using a queue-based waitlist. The system uses a JSON-based database for persistent storage, ensuring data consistency and transparency.

---

## Features

- **Bulk Reservations**: Users can book multiple seats at once, with real-time updates to availability and booking history.
- **Refund System**: Enables users to refund reservations while retaining visibility in the booking history.
- **Waitlist Management**: Implements a queue system that prioritizes users based on the order of their booking requests when seats become available.
- **Booking History**: Allows users to access their entire booking history, including refunded bookings, ensuring complete transparency.
- **Admin Panel**: Empowers admins to directly manage the database, including modifying bus schedules, bookings, and user records.

---

## Demo Walkthrough

### 1. Reservation Process:

- Simulate a bulk booking scenario where the system updates the database and booking history.
- Show changes to seat availability in real-time.

### 2. Refund Process:

- Demonstrate refunding a bulk reservation.
- Highlight how the refunded reservation remains visible in the booking history.

### 3. Waitlist System:

- Simulate a fully booked bus.
- Add users to the waitlist and show how the queue prioritizes earlier bookings when seats become available.

### 4. Database Interaction:

- Present live updates to the JSON database for reservations, refunds, and waitlist operations to emphasize transparency and real-time handling.

---

## Technical Highlights

### Libraries Used:

- **Nlohmann JSON**: Facilitates JSON parsing and storage for the database.
- **SHA1**: Generates unique identifiers for each reservation.

### Data Structures:

- **Queue**: Manages the waitlist to ensure fair prioritization.
- **Custom Classes**: Encapsulates logic for buses, reservations, and user data. and more.

### Database Design:

- JSON-based storage schema includes:
  - **Reservations**: Tracks booking details and statuses.
  - **Waitlist**: Manages users awaiting seat availability.
  - **Bus Schedules**: Contains bus details, including routes, seats, and availability.

---

## How to Run

### Prerequisites:

1. Install a C++ compiler (e.g., GCC or Clang).

### Setup:

1. ```bash
   git clone https://github.com/RaksaOC
   Bus-Management-System.git
   ```
2. ```bash
   cd Bus Management System/main
   ```
3. ```bash
   g++ -std=c++17 main.cpp -o main
   ```

4. ```bash
   ./main
   ```

---

## Future Improvements

- System Architecture: Improve modularity by redistributing class responsibilities and introducing helper classes.
- Algorithm Optimization: Reduce time complexity in operations such as seat allocation and data retrieval.
- Graphical Interface: Transition from CLI to a graphical user interface (GUI) using a library like Qt for enhanced usability.
- Real-Time Synchronization: Enable real-time synchronization for bus schedules and availability across multiple systems.

---

## Thank You

Thank you for exploring the Bus Management System! If you have questions, feedback, or ideas for improvement, feel free to reach out.

---
