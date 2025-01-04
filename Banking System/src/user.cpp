#include <iostream>
#include <fstream>
#include <cstring>

#include "../headers/user.h"
#include "../headers/transaction.h"

#include "../headers/user.h"

/**
 * @brief Constructs a User object with a specified ID and name.
 *
 * @param id The unique identifier for the user.
 * @param name The name of the user.
 * @return This constructor does not return a value.
 */
User::User(uint16_t id, std::string name) : id(id), name(std::move(name)) {}

/**
 * @brief Copy constructor for the User class.
 *
 * Creates a new User object by copying the id and name from another User instance.
 *
 * @param user The User object to be copied.
 * @return A new User object initialized with values from the provided User instance.
 */
User::User(const User &user) : id(user.id), name(user.name) {}

/**
 * @brief Move constructor for the User class.
 *
 * Constructs a new User instance by moving data from another User object.
 *
 * @param user An rvalue reference to another User object from which the data is moved.
 * @return A new User object with the data from the provided User object. The provided User object is left in a
 * valid but unspecified state.
 */
User::User(const User &&user) noexcept : id(user.id), name(std::move(user.name)) {}

/**
 * Overloaded assignment operator that copies the values from one User object to another.
 *
 * @param user The User object to copy the data from.
 * @return A reference to the current User object after assignment.
 */
User &User::operator=(const User &user) {
    if (this != &user) {
        id = user.id;
        name = user.name;
    }
    return *this;
}

/**
 * Retrieves the unique identifier (ID) of the user.
 *
 * @return The ID of the user as an unsigned 16-bit integer.
 */
const uint16_t User::getId() const {
    return id;
}

/**
 * @brief Retrieves the name of the user.
 *
 * @return A const reference to the name of the user as a std::string.
 */
const std::string &User::getName() const {
    return name;
}

/**
 * Prints the information of the specified user.
 *
 * @param user Reference to the User object whose information is to be printed.
 */
const void User::printUserInformation(const User &user) const {
    std::cout << "User ID: " << id << ", Name: " << name << std::endl;
}

