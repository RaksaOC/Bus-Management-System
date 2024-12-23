# Bus Reservation System

## Overview
The Bus Reservation System is a command-line application built using C++ that simulates a simplified reservation and refund system for bus bookings. It provides features for making bulk and single reservations, handling refunds, maintaining a waitlist, and viewing booking history.

## Features
- **Bulk Reservations:** Users can book multiple seats at once and view updates in real-time.
- **Refund System:** Allows users to refund a reservation while retaining visibility in their booking history.
- **Waitlist Management:** A queue-based system prioritizes users who booked earlier when seats become available.
- **Booking History:** Users can view all past bookings, including refunded ones, for record-keeping.
- **Admin Actions:** Admins can manipulate the database.

## Demo Walkthrough
1. **Reservation Process:**
   - Users make a bulk reservation.
   - The system updates seat availability and the user's booking history.
2. **Refund Process:**
   - Users can refund a bulk reservation they made earlier.
   - Booking history is retained for refunded entries, showing transparency.
3. **Waitlist System:**
   - Simulate a scenario where a bus is fully booked.
   - Add users to the waitlist.
   - Demonstrate how the queue prioritizes earlier bookings when seats become available.
4. **Database Interaction:**
   - Show the JSON database updates for key actions (e.g., reservation, refund, waitlist updates) to highlight real-time data handling.

## Technical Highlights
- **Libraries Used:**
  - [Nlohmann JSON](https://github.com/nlohmann/json): For handling JSON-based database storage.
  - SHA1: For generating unique reservation identifiers.
- **Data Structures:**
  - Queue: For implementing the waitlist system.
  - Custom Classes: Used for Users, Reservations, and Buses.
- **Database Design:**
  - JSON-based storage includes keys for reservation status, user data, and bus schedules.

## How to Run
1. **Prerequisites:**
   - Install a C++ compiler (e.g., GCC).
   - Ensure [Nlohmann JSON library](https://github.com/nlohmann/json) is included in the project.
2. **Setup:**
   - Clone the repository.
   - Build the project using a C++ compiler.
3. **Run the Program:**
   ```bash
   ./bus_reservation_system
   ```

## Sample JSON Database
Here's a sample of what the JSON database might look like:
```json
{
  "reservations": [
    {
      "id": "12345",
      "user": "JohnDoe",
      "seats": ["A1", "A2", "A3"],
      "status": "confirmed"
    }
  ],
  "waitlist": [
    {
      "user": "JaneDoe",
      "seats_requested": 2
    }
  ]
}
```

## Future Improvements
- **System Architecture:** Refactor for modularity by redistributing class responsibilities and adding helper classes.
- **Algorithm Optimization:** Optimize inefficient methods, such as reducing time complexity for data replacement.
- **GUI Implementation:** Transition from a command-line interface to a GUI using a library like Qt.
- **Real-Time Updates:** Enable dynamic, real-time synchronization for bus schedules and seat availability.

## Contributing
Contributions are welcome! Please fork the repository and create a pull request with your improvements.

## License
This project is open-source and available under the MIT License.

---
Thank you for exploring the Bus Reservation System! If you have questions or feedback, feel free to reach out.
