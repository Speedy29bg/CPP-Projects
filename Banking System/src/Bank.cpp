#include "../headers/Bank.h"
#include <iostream>
#include <algorithm> // for std::sort

/**
 * @brief Constructs a Bank instance with the specified users and transactions.
 *
 * @param users A vector containing the list of users to initialize the bank with.
 * @param transactions A vector containing the list of transactions to initialize the bank with.
 * @return None
 */
Bank::Bank(std::vector<User> users, std::vector<Transaction> transactions)
    : users(std::move(users)), transactions(std::move(transactions)) {}

/**
 * @brief Adds a new user to the bank's user list and increments the user count.
 *
 * @param user The user to be added to the bank. This parameter will be moved
 *             into the internal list of users.
 */
void Bank::addUser(User user) {
    users.push_back(std::move(user));
    userCount++;
}

/**
 * @brief Retrieves the list of users managed by the bank.
 *
 * This method returns all registered users within the bank system.
 * The users are stored as a vector of User objects.
 *
 * @return A vector containing all User objects managed by the bank.
 */
std::vector<User> Bank::getUsers() const {
    return users;
}

/**
 * Removes a user from the bank's user list based on their username.
 *
 * @param userName The name of the user to be deleted.
 * @return true if the user was found and successfully deleted, false otherwise.
 */
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

/**
 * Searches for a user in the bank system by their name.
 *
 * @param userName The name of the user to search for.
 * @param user Reference to a `User` object where the found user's details will be copied.
 * @return `true` if the user is found, `false` otherwise.
 */
bool Bank::findUser(const std::string& userName, User& user) const {
    for (const auto& u : users) {
        if (u.getName() == userName) {
            user = u;
            return true; // User found
        }
    }
    return false; // User not found
}

/**
 * Executes a financial transaction between two users, updates the system to track the transaction,
 * and writes the transaction data to the provided files.
 *
 * @param usersFile A file stream for the users' data file where changes will be saved.
 * @param blocksFile A file stream for the blocks' data file where transaction details will be recorded.
 * @param sender The user initiating the transaction and sending the coins.
 * @param receiver The recipient user receiving the coins.
 * @param coins The amount of coins to be transferred from sender to receiver.
 * @return True if the transaction is successfully completed and persisted, false otherwise.
 */
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

/**
 * @brief Adds a transaction to the bank's transaction list.
 *
 * This method stores a `Transaction` object in the bank's transaction list.
 * The ownership of the passed transaction is transferred to the bank.
 *
 * @param transaction The transaction to be added to the list.
 */
void Bank::addTransaction(Transaction transaction) {
    transactions.push_back(std::move(transaction));
}

/**
 * Prints the wealthiest users based on their wealth in descending order.
 * The method displays up to the specified number of users, and if the number
 * is greater than the total number of users available, all users are displayed.
 *
 * @param count The number of wealthiest users to display. If the value exceeds
 *        the total number of users, all users will be displayed.
 */
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

/**
 * @brief Prints the detailed information about the bank, including user count,
 * total amount of money, and a list of transactions.
 *
 * This method displays the following information:
 * - The total number of users in the bank.
 * - The total amount of money currently held by the bank.
 * - A detailed list of all transactions that have occurred,
 *   where each transaction's information is printed using the
 *   `printTransactionInformation` method of the `Transaction` class.
 *
 * @note This method is const-qualified, meaning it does not modify the state
 *       of the Bank object.
 */
void Bank::printBankInformation() const {
    std::cout << "Bank has " << userCount << " users.\n";
    std::cout << "Total amount of money in the bank: " << totalAmountOfMoney << "\n";

    std::cout << "Transactions:\n";
    for (const auto& transaction : transactions) {
        transaction.printTransactionInformation();
    }
}