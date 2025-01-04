#include "../headers/Bank.h"
#include <iostream>
#include <algorithm> // for std::sort

// Constructor with initialization
Bank::Bank(std::vector<User> users, std::vector<Transaction> transactions)
    : users(std::move(users)), transactions(std::move(transactions)) {}

// Add a user to the bank
void Bank::addUser(User user) {
    users.push_back(std::move(user));
    userCount++;
}

// Get all users in the bank
std::vector<User> Bank::getUsers() const {
    return users;
}

// Delete a user by name
bool Bank::deleteUser(const std::string& userName) {
    auto it = std::remove_if(users.begin(), users.end(),
                             [&userName](const User& user) { return user.getName() == userName; });

    if (it != users.end()) {
        users.erase(it, users.end());
        userCount--;
        return true; // User deleted successfully
    }
    return false; // User not found
}

// Find a user by name and return it by reference
bool Bank::findUser(const std::string& userName, User& user) const {
    for (const auto& u : users) {
        if (u.getName() == userName) {
            user = u;
            return true; // User found
        }
    }
    return false; // User not found
}

// Create a transaction between two users
bool Bank::makeTransaction(std::fstream& usersFile, std::fstream& blocksFile,
                           const User& sender, const User& receiver, double coins) {
    // Verify both users exist
    if (!Transaction::isValidUser(sender) || !Transaction::isValidUser(receiver)) {
        std::cerr << "Transaction failed: Invalid sender or receiver.\n";
        return false;
    }

    // Validate transaction and perform
    Transaction transaction(sender, receiver, coins, time(nullptr));
    if (!transaction.verifyTransaction(sender, receiver)) {
        std::cerr << "Transaction verification failed.\n";
        return false;
    }

    // Track the transaction in the bank
    addTransaction(transaction);

    // Persist transaction information (if necessary, implement saving logic)
    transaction.makeTransaction(usersFile, blocksFile, sender, receiver, coins);

    std::cout << "Transaction completed: " << sender.getName() << " sent " << coins
              << " coins to " << receiver.getName() << ".\n";
    return true;
}

// Add a transaction to the bank's list
void Bank::addTransaction(Transaction transaction) {
    transactions.push_back(std::move(transaction));
}

// Print the wealthiest users sorted by their total amount of money
void Bank::printWealthiestUsers(size_t count) const {
    if (count > users.size()) {
        count = users.size();
    }

    // Preparing a sorted copy of users by wealth
    auto sortedUsers = users;
    std::sort(sortedUsers.begin(), sortedUsers.end(),
              [](const User& a, const User& b) {
                  // Compare users by wealth (assuming wealth data is stored somewhere)
                  // Modify `getWealth()` to use actual wealth logic
                  return a.getWealth() > b.getWealth();
              });

    std::cout << "Top " << count << " wealthiest users:\n";
    for (size_t i = 0; i < count; ++i) {
        sortedUsers[i].printUserInformation(sortedUsers[i]);
    }
}

// Print all bank information
void Bank::printBankInformation() const {
    std::cout << "Bank has " << userCount << " users.\n";
    std::cout << "Total amount of money in the bank: " << totalAmountOfMoney << "\n";

    std::cout << "Transactions:\n";
    for (const auto& transaction : transactions) {
        transaction.printTransactionInformation();
    }
}