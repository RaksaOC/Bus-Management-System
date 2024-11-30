# `Route` Class Documentation

The `Route` class represents a bus route, including its origin, destination, optional stops, and schedule. It provides methods to manage and display route details.

The `Route` class encapsulates the details of a bus route, allowing the user to set the origin and destination, add intermediate stops, set the schedule, and view the route information.

---

## Attributes

### **Private Attributes**
| **Name**         | **Type**        | **Description**                                           |
|-------------------|-----------------|-----------------------------------------------------------|
| `origin`         | `string`       | The starting point of the route.                          |
| `destination`    | `string`       | The endpoint of the route.                                |
| `stops`          | `vector<string>` | A list of optional intermediate stops along the route.    |
| `schedule`       | `string`       | The schedule of the route (e.g., departure time).         |

---

## Methods

### **Public Methods**
| **Method**                                      | **Return Type** | **Description**                                                                   |
|-------------------------------------------------|-----------------|-----------------------------------------------------------------------------------|
| `Route(string origin, string destination)`     | `Constructor`   | Initializes a route with the specified origin and destination.                   |
| `void setRoute(string origin, string destination)` | `void`       | Sets or updates the route's origin and destination.                              |
| `void addStop(string stop)`                    | `void`          | Adds an intermediate stop to the route.                                          |
| `void setSchedule(string time)`                | `void`          | Sets the schedule for the route (e.g., departure time).                          |
| `void displayRouteDetails()`                   | `void`          | Displays route details, including origin, destination, stops, and schedule.      |

---

## Constructor

### `Route(string origin, string destination)`
- **Description**: Initializes a new `Route` object with the given origin and destination.
- **Parameters**:
  - `origin`: The starting point of the route.
  - `destination`: The endpoint of the route.
- **Behavior**:
  - Sets the `origin` and `destination` attributes.
  - Prepares the route for additional stops or scheduling.

---

## Method Details

### `void setRoute(string origin, string destination)`
- **Description**: Updates the route's origin and destination.
- **Parameters**:
  - `origin`: The new starting point of the route.
  - `destination`: The new endpoint of the route.
- **Behavior**:
  - Updates the `origin` and `destination` attributes.
  - **[TO DO]**: Implement functionality to save updated data to a file if needed.

---

### `void addStop(string stop)`
- **Description**: Adds an intermediate stop to the route.
- **Parameters**:
  - `stop`: The name of the stop to be added.
- **Behavior**:
  - Adds the `stop` to the `stops` vector.
  - Ensures no duplicates in the `stops` list if necessary.
- **[TO DO]**: Add logic for duplicate prevention if required.

---

### `void setSchedule(string time)`
- **Description**: Sets the schedule for the route.
- **Parameters**:
  - `time`: The schedule (e.g., departure time) for the route.
- **Behavior**:
  - Updates the `schedule` attribute.
  - **[TO DO]**: Validate and format the schedule string for consistency.

---

### `void displayRouteDetails()`
- **Description**: Displays the complete details of the route.
- **Behavior**:
  - Prints the following information:
    - Origin and destination of the route.
    - Any intermediate stops in the `stops` list.
    - The route schedule.
  - **[TO DO]**: Format the output for readability and completeness.

---

## Example Usage

```cpp
// to be documented
```