#include <iostream>
#include <fstream>
#include <cstring>
#include "../headers/user.h"
#include "../headers/transaction.h"


/**
 * Constructs a Transaction object with the specified sender, receiver, number of coins, and timestamp.
 *
 * @param sender The User who is sending the coins in this transaction.
 * @param receiver The User who is receiving the coins in this transaction.
 * @param coins The amount of coins being transferred in the transaction.
 * @param time The timestamp of when the transaction was created.
 */
Transaction::Transaction(User sender,
                         User receiver,
                         double coins,
                         long long time) {
    this->sender = sender;
    this->receiver = receiver;
    this->coins = coins;
    this->time = time;
}

/**
 * Computes a hash value for a given memory block using a custom hashing algorithm.
 *
 * @param memory A pointer to the memory block for which the hash is to be computed.
 * @param length The number of bytes in the memory block to process.
 * @return A 16-bit hash value generated from the input memory block.
 */
uint16_t Transaction::computeHash(const unsigned char *memory, int length)
{
    unsigned hash = 0xbeaf;

    for (int c = 0; c < length; c++)
    {
        hash += memory[c];
        hash += hash << 10;
        hash ^= hash >> 6;
    }

    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    return hash;
}

/**
 * @brief Prints transaction details including sender, receiver, amount of coins, and timestamp.
 *
 * This method displays detailed information regarding a transaction. It includes:
 * - The sender's name.
 * - The amount of coins transferred.
 * - The receiver's name.
 * - The time when the transaction occurred.
 *
 * The information is formatted for readability and printed directly to the standard output stream.
 *
 * @note The method has no return value.
 * @note This does not alter any member variables in the `Transaction` class.
 */
void Transaction::printTransactionInformation() const {
    std::cout << "Sender: "     << sender.getName()
              << "sent"         << coins << " Coins: "
              << "Receiver: "   << receiver.getName()
              << ", Time: "     << time << std::endl;
}

/**
 * Overloads the insertion operator to print the details of a transaction.
 *
 * @param transaction The transaction object whose details are to be displayed.
 */
void Transaction::operator<<(const Transaction &transaction) const {

    std::cout << "Transaction: " << transaction.sender.getName() << " sent " << transaction.coins << " coins to " << transaction.receiver.getName() << std::endl;
    std::cout << "Time: "        << transaction.time << std::endl;
    std::cout << std::endl;
}

/**
 * Checks whether the provided user is valid.
 *
 * A valid user is defined as one with a non-zero ID and
 * a non-empty name.
 *
 * @param user A reference to the User object to validate.
 * @return true if the user is valid, false otherwise.
 */
bool Transaction::isValidUser(const User &user) {
       return user.getId() != 0 && !user.getName().empty();
   }

/**
 * Verifies the validity of the transaction by checking sender and receiver details.
 *
 * This method validates if both the sender and receiver are valid users,
 * and verifies that their details match the transaction's stored data.
 * Additional checks can be implemented as needed (e.g., cryptographic or balance checks).
 *
 * @param sender The sender user involved in the transaction.
 * @param receiver The receiver user involved in the transaction.
 * @return True if the transaction is valid, otherwise false.
 */
bool Transaction::verifyTransaction(const User& sender, const User& receiver) const {
    try {
        // Check if sender and receiver are valid users
        if (!isValidUser(sender) || !isValidUser(receiver)) {
            throw std::invalid_argument("Invalid sender or receiver.");
        }

        // Check if sender and receiver match this transaction's sender and receiver
        if (this->sender.getId()    != sender.getId() ||
            this->receiver.getId()  != receiver.getId()) {
            throw std::logic_error("Transaction details do not match sender or receiver.");
        }

        // Add any additional checks here (e.g., balance verification, cryptographic checks)

        return true; // If all checks pass, the transaction is valid
    } catch (...) {
        // Catch any exceptions, silently handle or log the error if necessary
        return false;
    }
}

