#include "transaction.h"
#include "user.h"
#include <sstream>
#include <stdexcept>
#include <ctime>

/**
 * Constructs a Transaction object to record a transfer of coins between two users.
 * Validates that the transaction meets the minimum coin threshold and that the
 * sender has sufficient balance to complete the transaction.
 *
 * @param sender The User object representing the sender of the transaction.
 * @param receiver The User object representing the receiver of the transaction.
 * @param coins The amount of coins being transferred in the transaction.
 * @param time The timestamp indicating when the transaction occurred.
 * @throw std::invalid_argument If the transaction amount is below the minimum threshold.
 * @throw std::invalid_argument If the sender has insufficient balance for the transaction.
 */
Transaction::Transaction(const User& sender,
                         const User& receiver,
                         double coins,
                         long long time)
    : sender(sender), receiver(receiver), coins(coins), time(time) {
    if (coins < MINIMUM_COINS) {
        throw std::invalid_argument("Transaction failed: Amount is below the minimum threshold.");
    }
    if (sender.getBalance() < coins) {
        throw std::invalid_argument("Transaction failed: Sender's balance is insufficient.");
    }
}

/**
 * Computes a 16-bit hash value for the given input string data.
 * The hash value is calculated using a combination of
 * bitwise operations and arithmetic manipulation for consistency.
 *
 * @param data The input string for which the hash value is to be computed.
 * @return A 16-bit unsigned integer representing the hash of the input string.
 */
uint16_t Transaction::computeHash(const std::string& data) {
    unsigned hash = 0xbeef; // A seed value

    for (char c : data) {
        hash += c;
        hash += hash << 10;
        hash ^= hash >> 6;
    }

    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;

    return static_cast<uint16_t>(hash);
}

/**
 * @brief Prints the information of the transaction to the standard output.
 *
 * This method outputs the details of a transaction to the console, including:
 * - The name of the sender.
 * - The amount of coins transferred.
 * - The name of the receiver.
 * - The timestamp of the transaction.
 *
 * The output is formatted as:
 * "Transaction: [sender_name] sent [coins] coins to [receiver_name] at time [timestamp]"
 *
 * @note This function does not modify the state of the transaction object.
 */
void Transaction::printTransactionInformation() const {
    std::cout << "Transaction: "
              << sender.getName() << " sent " << coins
              << " coins to " << receiver.getName()
              << " at time " << time << std::endl;
}

/**
 * Overloaded output stream operator for printing the details of a Transaction object.
 *
 * @param os The output stream where the transaction details will be written.
 * @param transaction The Transaction object whose details are to be written to the output stream.
 * @return A reference to the output stream after writing the transaction details.
 */
std::ostream& operator<<(std::ostream& os, const Transaction& transaction) {
    os << "Sender: " << transaction.sender.getName()
       << ", Receiver: " << transaction.receiver.getName()
       << ", Coins: " << transaction.coins
       << ", Time: " << transaction.time;
    return os;
}

/**
 * Verifies the validity of the current transaction.
 *
 * A transaction is considered valid if the amount of coins
 * being transferred meets the minimum transaction requirement
 * and the sender has an adequate balance to cover the transfer.
 *
 * @return true if the transaction is valid, false otherwise.
 */
bool Transaction::verifyTransaction() const {
    if (coins < MINIMUM_COINS) return false;
    if (sender.getBalance() < coins) return false;
    return true;
}