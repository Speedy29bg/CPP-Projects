#ifndef BANK_H
#define BANK_H

#include "transaction.h"
#include "user.h"
#include <vector>

class Bank {
private:
    std::vector<User> users;              // List of users
    std::vector<Transaction> transactions; // List of transactions
    int userCount{};                      // Count of users
    long long totalAmountOfMoney{};       // Total amount of money in system

public:
    Bank() = default;
    Bank(std::vector<User> users, std::vector<Transaction> transactions);

    // Core functionality
    void addUser(User user);                      // Add a user
    bool deleteUser(const std::string& userName); // Delete a user by name
    bool findUser(const std::string& userName, User& user) const; // Find a user by name
    std::vector<User> getUsers() const;           // Get all users
    bool makeTransaction(std::fstream& usersFile, std::fstream& blocksFile,
                         const User& sender, const User& receiver, double coins); // Make a transaction

    // Transactions management
    void addTransaction(Transaction transaction); // Add a transaction

    // Reporting and information
    void printWealthiestUsers(size_t count) const; // Print wealthiest users
    void printBankInformation() const;            // Print bank info

    ~Bank() = default; // Default destructor
};

#endif


