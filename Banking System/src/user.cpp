#include <iostream>
#include <fstream>
#include <cstring>

#include "../headers/user.h"
#include "../headers/transaction.h"


/**
 * Constructor for the User class.
 *
 * @param id The unique identifier for the user.
 * @param name The name of the user.
 * @param balance The initial balance of the user. Defaults to 0.0 if not provided.
 * @return A new instance of the User class initialized with the provided values.
 */
User::User(uint16_t id, std::string name, double balance)
    : id(id), name(std::move(name)), balance(balance) {}

/**
 * @brief Prints the user's information to the standard output.
 *
 * Displays the user's ID, name, and current balance in a formatted manner.
 * This method is intended for providing a quick summary of the user's details.
 *
 * @note This function does not modify the state of the User object.
 */
void User::printUserInformation() const {
    std::cout << "User ID: " << id << "\n"
              << "Name: " << name << "\n"
              << "Balance: " << balance << "\n";
}