#include "bank.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>

/**
 * @brief Adds a new user to the bank's list of users.
 *
 * @param user A constant reference to the User object to be added to the bank.
 */
void Bank::addUser(const User& user) {
    users.push_back(user);
}

/**
 * Removes a user with the specified user name from the bank's user list.
 *
 * @param userName The name of the user to be deleted.
 * @return True if a user with the given name was found and removed successfully,
 *         false if no such user exists in the bank.
 */
bool Bank::deleteUser(const std::string& userName) {
    auto it = std::remove_if(users.begin(), users.end(), [&](const User& u) {
        return u.getName() == userName;
    });

    if (it != users.end()) {
        users.erase(it, users.end());
        return true;
    }
    return false;
}

/**
 * Finds a user in the bank's user list by their username.
 *
 * @param userName The username of the user to search for.
 * @param user A reference to a User object where the found user's details will be stored.
 * @return true if a user with the specified username is found, false otherwise.
 */
bool Bank::findUser(const std::string& userName, User& user) const {
    for (const auto& u : users) {
        if (u.getName() == userName) {
            user = u;
            return true;
        }
    }
    return false;
}

/**
 * @brief Facilitates a transaction between two users, transferring coins from the sender to the receiver.
 *
 * This method validates the transaction by ensuring the sender has sufficient balance
 * and the transaction amount meets the minimum required threshold. If the transaction
 * is successfully verified, it is added to the list of transactions.
 *
 * @param sender The user initiating the transaction.
 * @param receiver The user receiving the transaction amount.
 * @param coins The amount of coins to be transferred from sender to receiver.
 *
 * @throws std::invalid_argument If the transaction amount is less than the minimum allowed or
 *                                if the sender has insufficient balance.
 */
void Bank::makeTransaction(const User& sender, const User& receiver, double coins) {
    if (coins < MINIMUM_COINS) {
        throw std::invalid_argument("Transaction amount is too small.");
    }
    if (sender.getBalance() < coins) {
        throw std::invalid_argument("Insufficient balance.");
    }

    Transaction transaction(sender, receiver, coins, time(nullptr));
    if (transaction.verifyTransaction()) {
        transactions.push_back(transaction);
        std::cout << "Transaction successful: " << transaction << std::endl;
    } else {
        std::cerr << "Transaction validation failed." << std::endl;
    }
}

/**
 * Prints information about the wealthiest users managed by the bank.
 * The users are sorted by their balances in descending order, and the top
 * `count` users are displayed. If the total number of users is less than `count`,
 * all users are displayed.
 *
 * @param count The number of top wealthiest users to print. If this value exceeds
 *              the total number of users, all users will be printed.
 */
void Bank::printWealthiestUsers(size_t count) const {
    auto sortedUsers = users;
    std::sort(sortedUsers.begin(), sortedUsers.end(),
              [](const User& a, const User& b) {
                  return a.getBalance() > b.getBalance();
              });

    for (size_t i = 0; i < std::min(count, sortedUsers.size()); ++i) {
        sortedUsers[i].printUserInformation();
    }
}