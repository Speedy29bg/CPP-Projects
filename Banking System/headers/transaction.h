#pragma once

#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include "user.h" // Only include related files
class Bank;

constexpr double MINIMUM_COINS = 0.01; // Constant for transaction validation

/**
 * @class Transaction
 * @brief Represents a financial transaction between two users.
 *
 * The Transaction class encapsulates the details of a financial transaction,
 * including the sender, receiver, amount of coins, and the timestamp. It provides
 * functionality to verify the validity of a transaction, compute hashes for security,
 * and print transaction details.
 */
class Transaction {
private:
    User sender;      // Sender of the transaction
    User receiver;    // Receiver of the transaction
    double coins {};  // Transaction amount
    long long time {}; // Timestamp for transaction

public:
    // Constructors
    Transaction() = default; // Default constructor
    Transaction(const User& sender,
                const User& receiver,
                double coins,
                long long time);

    // Core functionality
    bool verifyTransaction() const; // Verifies the transaction details
    static uint16_t computeHash(const std::string& data); // Safe hash computation
    void printTransactionInformation() const; // Print transaction details

    // Friend insertion operator for printing
    friend std::ostream& operator<<(std::ostream& os, const Transaction& transaction);

    ~Transaction() = default; // Default destructor
};