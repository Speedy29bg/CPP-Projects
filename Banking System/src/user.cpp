#include <iostream>
#include <fstream>
#include <cstring>

#include "../headers/user.h"
#include "../headers/transaction.h"

#include "../headers/user.h"

// Constructor implementation
User::User(uint16_t id, std::string name) : id(id), name(std::move(name)) {}

// Copy constructor
User::User(const User &user) : id(user.id), name(user.name) {}

// Move constructor
User::User(const User &&user) noexcept : id(user.id), name(std::move(user.name)) {}

// Assign user
User &User::operator=(const User &user) {
    if (this != &user) {
        id = user.id;
        name = user.name;
    }
    return *this;
}

// Getters
const uint16_t User::getId() const {
    return id;
}

const std::string &User::getName() const {
    return name;
}

// Print User Information
const void User::printUserInformation(const User &user) const {
    std::cout << "User ID: " << id << ", Name: " << name << std::endl;
}

