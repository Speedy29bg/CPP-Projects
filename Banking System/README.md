# Banking System Project

## Overview
The **Banking System Project** is a simulation of a simple banking system implemented in C++. It allows for the management of users, transactions, and tracking financial activities using a blockchain-like structure. The system is designed for educational purposes and demonstrates various programming concepts like object-oriented programming, exception handling, data validation, and the use of constructors/destructors.

## Features
- **User Management**: Add, delete, and find users with their associated information (ID, name, and account balance).
- **Transaction Management**: Conduct validated financial transactions between users.
- **Blockchain Implementation**: Maintain a chain of transactions using `TransactionBlock` to store metadata.
- **Customizable Reports**:
    - Display the wealthiest users in the bank.
    - Print details of transactions and users.
- **Transaction Validation**:
    - Minimum amount threshold for transactions.
    - Verification of sufficient balance for transactions.
- Extensive error handling for invalid operations.

## File Structure
The project is structured as follows:
## Key Classes
### 1. **User**
Represents a user with:
- A unique ID, name, and account balance.
- Methods for managing and printing user information.

### 2. **Transaction**
Simulates a financial transaction between two users:
- Validates transaction constraints such as minimum amount and sufficient balance.
- Supports verification mechanisms and informative printing.

### 3. **TransactionBlock**
Represents a block in a blockchain-like ledger system:
- Contains metadata such as transaction ID, previous block hash, and a count of valid transactions.
- Functions to validate and manage block information.

### 4. **Bank**
Handles the overall banking system:
- Manages a list of users and transactions.
- Facilitates operations such as:
    - Adding/removing users.
    - Conducting validated transactions.
    - Printing customized reports.

## How to Build
### Prerequisites
- **CMake** version 3.30 or higher.
- A C++14-compatible compiler (e.g., GCC, Clang, or MSVC).

### Build Instructions
1. Clone the repository or copy the project files into a directory.
2. Open a terminal and navigate to the project directory.
3. Generate a build system with CMake:
   ```
   cmake -S . -B build
   ```
4. Compile the project:
   ```
   cmake --build build
   ```
5. The executable `CPP_Projects` will be created in the `build` directory.

## How to Run
1. After building the project, navigate to the `build` directory:
   ```
   cd build
   ```
2. Run the executable:
   ```
   ./CPP_Projects
   ```
3. Interact with the system as per the main program logic.

## Sample Usage Demonstrated in `main.cpp`
- Adding users to the system:
    1. Alice with $500.
    2. Bob with $300.
    3. Charlie with $120.
    4. Diana with $800.
- Conducting transactions:
    1. Alice transfers $50 to Bob.
    2. Diana transfers $100 to Charlie.
- Displaying the wealthiest users before and after transactions.
- Handling invalid operations (e.g., insufficient balance).
- Visualizing a transaction block with metadata.

## Error Handling
- System exceptions are handled with descriptive error messages.
- Invalid transactions (e.g., insufficient balance, zero transaction amount) are gracefully managed with exceptions.

## Future Improvements
- Expand data persistence for users and transactions using file I/O.
- Add a GUI or CLI interaction for dynamic user input.
- Introduce cryptographic hashing for a more realistic blockchain implementation.

## Dependencies
This project has no external dependencies beyond standard C++ libraries.

## License
This project is open-source and free to use.

## Acknowledgments
This project demonstrates object-oriented programming and basic principles of blockchain technology in C++. It serves as a learning resource for beginner-intermediate developers exploring C++.