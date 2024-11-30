# `Bus` Class Documentation

The `Bus` class represents a bus in the system, including its attributes, seat management, and routing functionalities.

The `Bus` class handles the core features of a bus, such as managing seat availability, reserving seats, and associating routes with the bus. Each bus has a unique ID, type, seating capacity, seat pricing, and a status for each seat.

---

## Attributes

### **Private Attributes**
| **Name**        | **Type**             | **Description**                                      |
|------------------|----------------------|------------------------------------------------------|
| `busID`         | `string`            | Unique identifier for the bus.                      |
| `busType`       | `string`            | Type of bus (e.g., luxury, economy).                |
| `seatCap`       | `int`               | Total seating capacity of the bus.                  |
| `seatPrice`     | `int`               | Price per seat.                                     |
| `seatStatus`    | `vector<int>`       | Tracks seat availability (`0 = available`, `1 = reserved`). |

---

## Methods

### **Public Methods**
| **Method**                                    | **Return Type** | **Description**                                                                 |
|-----------------------------------------------|------------------|---------------------------------------------------------------------------------|
| `Bus(string ID, string type, int cap, int price)` | `Constructor`   | Initializes a bus object with its ID, type, seating capacity, and seat price.  |
| `void showSeatLayout()`                       | `void`          | Displays the current seating layout, showing which seats are available or reserved. |
| `bool reserveSeat(int seat)`                  | `bool`          | Reserves a specific seat if it is available. Returns `true` if successful.      |
| `bool reserveSeats(vector<int> seats)`        | `bool`          | Reserves multiple seats if all are available. Returns `true` if successful.    |
| `bool isSeatAvailable(int seat)`             | `bool`          | Checks if a specific seat is available. Returns `true` if available.           |
| `void setRoute(string origin, string destination)` | `void`         | Sets a route for the bus.                                                      |

---

## Constructor

### `Bus(string ID, string type, int cap, int price)`
- **Description**: Initializes a new bus object with the given parameters.
- **Parameters**:
  - `ID`: A unique identifier for the bus.
  - `type`: The type of bus (e.g., luxury, economy).
  - `cap`: The total seating capacity of the bus.
  - `price`: The price per seat.
- **Behavior**:
  - Initializes the `seatStatus` vector with all seats marked as available (`0`).

---

## Method Details

### `void showSeatLayout()`
- **Description**: Displays the current seat layout of the bus, showing each seat's availability.
- **Behavior**:
  - Iterates through the `seatStatus` vector.
  - Outputs each seat's number and its status (available or reserved).
- **[TO DO]**: Implement the display logic.

---

### `bool reserveSeat(int seat)`
- **Description**: Reserves a single seat if it is available.
- **Parameters**:
  - `seat`: The seat number to reserve.
- **Return Value**: 
  - Returns `true` if the seat is successfully reserved.
  - Returns `false` if the seat is already reserved or invalid.
- **[TO DO]**: Implement the reservation logic.

---

### `bool reserveSeats(vector<int> seats)`
- **Description**: Attempts to reserve multiple seats if all are available.
- **Parameters**:
  - `seats`: A vector of seat numbers to reserve.
- **Return Value**:
  - Returns `true` if all seats are successfully reserved.
  - Returns `false` if one or more seats are unavailable.
- **[TO DO]**: Implement the logic to check availability and reserve seats.

---

### `bool isSeatAvailable(int seat)`
- **Description**: Checks if a specific seat is available for reservation.
- **Parameters**:
  - `seat`: The seat number to check.
- **Return Value**:
  - Returns `true` if the seat is available (`seatStatus[seat] == 0`).
  - Returns `false` if the seat is already reserved or invalid.
- **[TO DO]**: Implement bounds checking and status verification.

---

### `void setRoute(string origin, string destination)`
- **Description**: Associates a route with the bus.
- **Parameters**:
  - `origin`: The starting point of the route.
  - `destination`: The endpoint of the route.
- **Behavior**:
  - Creates a `Route` object with the given `origin` and `destination`.
  - Saves or updates the route information for the bus.
- **[TO DO]**: Implement persistent storage if needed.

---

## Dependencies

|Header	           |             Description                   |
|------------------|-------------------------------------------|
|Route.hpp	       |Contains the definition of the Route class.|

## Example Usage

```cpp
\\ to be documented
```