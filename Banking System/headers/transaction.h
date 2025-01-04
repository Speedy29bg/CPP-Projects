
#ifndef HOMEWORK1_TRANSACTION_H
#define HOMEWORK1_TRANSACTION_H
#include <cstdint>
#include <fstream>

#include "user.h"
constexpr double MINIMUM_COINS = 0.01; // Extracted constant for better readability

class Transaction : public User
{
private:
    User sender;
    User receiver;
    double coins;
    long long time;

public:
    Transaction() = default;
    Transaction(User sender,
                User receiver,
                double coins,
                long long time);

    void operator<<(const Transaction &transaction) const;

    static uint16_t computeHash(const unsigned char *memory, int length);
    bool verifyTransaction(const User &sender, const User &receiver) const;
    static bool isValidUser(const User &user) ;
    void printTransactionInformation()const;
    void makeTransaction(std::fstream & usersFile,std::fstream & blocksFile , User sender, User receiver, double coins);

    ~Transaction() = default;
};



void biggestBlocks(size_t count);

#endif // HOMEWORK1_TRANSACTION_H