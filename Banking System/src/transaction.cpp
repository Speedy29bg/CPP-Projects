#include <iostream>
#include <fstream>
#include <cstring>
#include "../headers/user.h"
#include "../headers/transaction.h"


Transaction::Transaction(User sender,
                         User receiver,
                         double coins,
                         long long time) {
    this->sender = sender;
    this->receiver = receiver;
    this->coins = coins;
    this->time = time;
}

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

void Transaction::printTransactionInformation() const {
    std::cout << "Sender: "     << sender.getName()
              << "sent"         << coins << " Coins: "
              << "Receiver: "   << receiver.getName()
              << ", Time: "     << time << std::endl;
}

void Transaction::operator<<(const Transaction &transaction) const {

    std::cout << "Transaction: " << transaction.sender.getName() << " sent " << transaction.coins << " coins to " << transaction.receiver.getName() << std::endl;
    std::cout << "Time: "        << transaction.time << std::endl;
    std::cout << std::endl;
}

bool Transaction::isValidUser(const User &user) {
       return user.getId() != 0 && !user.getName().empty();
   }

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

