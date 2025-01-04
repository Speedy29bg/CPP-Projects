#include <iostream>
#include <fstream>
#include <cstring>

#include "Bank.h"
#include "../headers/user.h"
#include "../headers/run.h"
#include "../headers/transaction.h"

/**
 * Main function to manage a banking system, handling user creation, deletion,
 * transactions, and displaying user information.
 *
 * This function initializes the banking system, loads data from files, and allows
 * the user to interact with the system through a command-based menu interface.
 *
 * @return Returns 0 upon successful execution and proper cleanup of resources.
 * Returns 1 if necessary files for storing data cannot be opened.
 */
int main() {
    Bank bank;  // Bank class to manage users and transactions globally.

    // Open required files for persisting user and block data.
    std::fstream blocksFile("blocks.dat", std::ios::binary | std::ios::app | std::ios::in | std::ios::out);
    std::fstream usersFile("users.dat", std::ios::binary | std::ios::app | std::ios::in | std::ios::out);

    // Handle file operation issues.
    if (!blocksFile.is_open() || !usersFile.is_open()) {
        std::cout << "Error: Unable to open necessary files for storing data.\n";
        return 1; // Signal failure if files cannot be opened.
    }

    std::cout << "Successfully loaded data from files.\n";

    menu();  // Show the menu to the user.

    char command[128];  // Buffer for inputting commands.
    while (true) {
        std::cout << "\nEnter your command: ";
        std::cin.getline(command, sizeof(command));

        // Handle specific commands.
        if (strcmp(command, "create-user") == 0) {
            char userName[128];
            std::cout << "Enter user name: ";
            std::cin.getline(userName, sizeof(userName));

            uint16_t userId;
            std::cout << "Enter user ID: ";
            std::cin >> userId;
            std::cin.ignore(); // Flush the newline character.

            // Create new user and add to the system.
            User newUser(userId, userName);
            bank.addUser(newUser);
            std::cout << "User created successfully.\n";
        }
        else if (strcmp(command, "print") == 0) {
            // Print all users from the system.
            for (const User& user : bank.getUsers()) {  // Assuming a `getUsers()` method in `Bank`.
                user.printUserInformation(user);
            }
        }
        else if (strcmp(command, "print-users-coins") == 0) {
            // Show user balances (assuming `printUsersCoins()` is implemented).
            printUsersCoins(usersFile, blocksFile);
        }
        else if (strcmp(command, "delete-user") == 0) {
            char userName[128];
            std::cout << "Enter the name of the user to delete: ";
            std::cin.getline(userName, sizeof(userName));

            // Delete user via Bank class method (assuming `deleteUser()` method exists).
            if (bank.deleteUser(userName)) {
                std::cout << "User deleted successfully.\n";
            } else {
                std::cout << "Error: User not found or could not be deleted.\n";
            }
        }
        else if (strcmp(command, "make-transaction") == 0) {
            char senderName[128], receiverName[128];
            size_t amount;

            std::cout << "Enter sender name: ";
            std::cin.getline(senderName, sizeof(senderName));
            std::cout << "Enter receiver name: ";
            std::cin.getline(receiverName, sizeof(receiverName));
            std::cout << "Enter amount: ";
            std::cin >> amount;
            std::cin.ignore(); // Flush the newline character.

            User sender, receiver;

            // Find users in Bank system (assuming `findUser()` is implemented).
            bool senderFound = bank.findUser(senderName, sender);
            bool receiverFound = bank.findUser(receiverName, receiver);

            if (senderFound && receiverFound) {
                bank.makeTransaction(usersFile, blocksFile, sender, receiver, static_cast<double>(amount));
                std::cout << "Transaction completed successfully.\n";
            } else {
                std::cout << "Error: One or both users not found.\n";
            }
        }
        else if (strcmp(command, "wealthiest-users") == 0) {
            size_t count;
            std::cout << "Enter the number of wealthiest users to display: ";
            std::cin >> count;
            std::cin.ignore(); // Flush newline character.

            bank.printWealthiestUsers(count);
        }
        else if (strcmp(command, "exit") == 0) {
            // Exit the program.
            std::cout << "Exiting program.\n";
            break;
        }
        else {
            std::cout << "Invalid command. Please try again.\n";
            menu();  // Re-display the menu if an invalid command is entered.
        }
    }

    // Close the files for cleanup.
    blocksFile.close();
    usersFile.close();

    return 0;
}