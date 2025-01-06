#pragma once

#include <string>
#include <iostream>
#include <cstdint>

/**
 * @brief Represents a User with an ID, name, and account balance.
 *
 * The User class encapsulates information about a user including
 * a unique identifier (ID), the user's name, and their account balance.
 * It offers getters, setters, and utility functions for managing
 * and displaying user information.
 */
class User {
private:
    uint16_t id {};
    std::string name;
    double balance {}; // Stores the user's current balance

public:
    // Constructors
    User() = default;
    User(uint16_t id, std::string name, double balance = 0.0);

    // Getters
    uint16_t getId() const { return id; }
    const std::string& getName() const { return name; }
    double getBalance() const { return balance; }

    // Setters
    void setBalance(double newBalance) { balance = newBalance; }

    // Utility
    void printUserInformation() const;

    ~User() = default; // Default destructor
};