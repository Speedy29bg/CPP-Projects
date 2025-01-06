#pragma once

#include <vector>
#include "user.h"
#include "transaction.h"

/**
 * @class Bank
 * @brief Represents a banking system that manages users and their transactions.
 *
 * The Bank class provides functionalities to manage users, execute transactions
 * between them, and generate reports such as displaying the wealthiest users.
 */
class Bank {
private:
    std::vector<User> users; // List of users managed by the bank
    std::vector<Transaction> transactions; // List of all transactions

public:
    // Core functionality
    void addUser(const User& user);
    bool deleteUser(const std::string& userName);
    bool findUser(const std::string& userName, User& user) const;

    // Transactions
    void makeTransaction(const User& sender, const User& receiver, double coins);

    // Reports
    void printWealthiestUsers(size_t count) const;

    ~Bank() = default;
};