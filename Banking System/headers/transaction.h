
#ifndef HOMEWORK1_TRANSACTION_H
#define HOMEWORK1_TRANSACTION_H

struct Transaction
{
    unsigned sender;
    unsigned receiver;
    double coins;
    long long time;
};

struct TransactionBlock
{
    unsigned id;
    unsigned prevBlockId;
    unsigned prevBlockHash;
    int validTransactions;
    Transaction transactions[16];
};

unsigned computeHash(const unsigned char *memory, int length);
void makeTransaction(std::fstream & usersFile,std::fstream & blocksFile , User sender, User receiver, double coins);
TransactionBlock makeBlock(TransactionBlock prevBlock, Transaction transactions[16], int validTransactions);
void verifyTransactions();
void biggestBlocks(size_t count);

#endif // HOMEWORK1_TRANSACTION_H


// Transaction transaction;
    // transaction.sender = sender.id;
    // transaction.receiver = receiver.id;
    // transaction.coins = coins;
    // transaction.time = time(nullptr);
    // TransactionBlock block;
    // blocksFile.read((char *)&block, sizeof(TransactionBlock));
    // while (!blocksFile.eof())
    // {
    //     blocksFile.read((char *)&block, sizeof(TransactionBlock));
    // }
    // TransactionBlock newBlock = makeBlock(block, &transaction, 1);
    // blocksFile.write((char *)&newBlock, sizeof(TransactionBlock));
    // blocksFile.clear();
    // usersFile.seekg(0, std::ios::beg);
    // User user;
    // usersFile.read((char *)&user, sizeof(User));
    // while (!usersFile.eof())
    // {
    //     if (user.id == sender.id)
    //     {
    //         transaction.coins -= coins;
    //     }
    //     else if (user.id == receiver.id)
    //     {
    //         transaction.coins += coins;
    //     }
    //     usersFile.read((char *)&user, sizeof(User));
    // }