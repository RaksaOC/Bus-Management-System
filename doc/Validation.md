# Login Validation Module

This module provides foundational validation functions to ensure secure and accurate user authentication during login. While the current implementation focuses on basic functionality, it is structured to allow future expansions and enhancements.

## Features

### `isNameValid(string fName, string lName)`

- **Purpose**: Validates the user's full name.
- **Checks**:
  - Ensures the name does not contain numbers or punctuation.
  - Combines the first and last names for validation.

### `isAgeValid(int age)`

- **Purpose**: Validates the user's age.
- **Checks**:
  - Ensures the age is between 13 and 110.
  - Displays specific error messages for invalid age ranges.

### `isEmailAvailable(string email)`

- **Purpose**: Checks if the provided email is available.
- **Checks**:
  - Reads from the `Data.json` database.
  - Validates email uniqueness in the "users" section.

### `isEmailValid(string email)`

- **Purpose**: Validates the email format.
- **Checks**:
  - Ensures the email contains `@gmail.com`.
  - Returns an error for other formats.

### `isPasswordValid(string pass)`

- **Purpose**: Checks password validity.
- **Checks**:
  - Ensures the password is at least 6 characters long.
  - (Future enhancement: Add checks for complexity, e.g., symbols, uppercase letters).

### `isPasswordSame(string pass1, string pass2)`

- **Purpose**: Validates password confirmation.
- **Checks**:
  - Ensures the re-entered password matches the original.

### Utility Functions

#### `toLowerInput(string i)`

- Converts all characters in the input string to lowercase for consistent validation.

#### `capName(string n)`

- Capitalizes the first character of the given name string.

---

## There are more validation functions to come

### Future Expansion

- Add multi-domain email validation.
- Include stricter password rules (e.g., requiring symbols, numbers).
- Introduce more robust error-handling mechanisms. etc
