#include <iostream>
#include <fstream>
#include <cstring>
#include "../headers/user.h"
#include "../headers/transaction.h"

unsigned computeHash(const unsigned char *memory, int length)
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

double moneyToOOPCoin(double amountOfMoney)
{
    return amountOfMoney * 420;
}

void makeTransaction(std::fstream &usersFile, std::fstream &blocksFile, User sender, User receiver, double coins)
{
    Transaction* transaction = new Transaction();
    transaction->sender = sender.id;
    transaction->receiver = receiver.id;
    transaction->coins = coins;
    transaction->time = time(nullptr);
    TransactionBlock block;
    blocksFile.read((char *)&block, sizeof(TransactionBlock));
    while (!blocksFile.eof())
    {
        blocksFile.read((char *)&block, sizeof(TransactionBlock));
    }
    TransactionBlock newBlock = makeBlock(block, transaction, 1);
    blocksFile.write((char *)&newBlock, sizeof(TransactionBlock));
    blocksFile.clear();
    usersFile.seekg(0, std::ios::beg);
    User user;
    usersFile.read((char *)&user, sizeof(User));
    while (!usersFile.eof())
    {
        if (user.id == sender.id)
        {
            transaction->coins -= coins;
        }
        else if (user.id == receiver.id)
        {
            transaction->coins += coins;
        }
        usersFile.read((char *)&user, sizeof(User));
    }
    usersFile.clear();
    usersFile.seekp(0, std::ios::beg);
    usersFile.write((char *)&user, sizeof(User));
    usersFile.clear();
}

TransactionBlock makeBlock(TransactionBlock prevBlock, Transaction transactions[16], int validTransactions)
{
    TransactionBlock block;
    block.id = prevBlock.id + 1;
    block.prevBlockId = prevBlock.id;
    block.prevBlockHash = computeHash((unsigned char *)&prevBlock, sizeof(TransactionBlock));
    block.validTransactions = validTransactions;
    for (int i = 0; i < validTransactions; i++)
    {
        block.transactions[i] = transactions[i];
    }
    return block;
}
void sendCoins(std::fstream &blocksFile, std::fstream &usersFile, User sender, User receiver, double coins)
{
    Transaction transaction;
    transaction.sender = sender.id;
    transaction.receiver = receiver.id;
    transaction.coins = coins;
    transaction.time = time(nullptr);
    TransactionBlock block;
    blocksFile.read((char *)&block, sizeof(TransactionBlock));
    while (!blocksFile.eof())
    {
        blocksFile.read((char *)&block, sizeof(TransactionBlock));
    }
    TransactionBlock newBlock = makeBlock(block, &transaction, 1);
    blocksFile.write((char *)&newBlock, sizeof(TransactionBlock));
    blocksFile.clear();
    usersFile.seekg(0, std::ios::beg);
    User user;
    usersFile.read(reinterpret_cast<char*>(&user), sizeof(User));
    while (!usersFile.eof())
    {
        if (user.id == sender.id)
        {
            transaction.coins -= moneyToOOPCoin(coins);
            usersFile.seekp(-sizeof(User), std::ios::cur);
            usersFile.write(reinterpret_cast<char *>(&user), sizeof(User));
            usersFile.clear();
        }
        else if (user.id == receiver.id)
        {
            transaction.coins += moneyToOOPCoin(coins);
            usersFile.seekp(-sizeof(User), std::ios::cur);
            usersFile.write((char *)&user, sizeof(User));
            usersFile.clear();
        }
        usersFile.read((char *)&user, sizeof(User));
    }
    usersFile.clear();
}

// void verifyTransactions()
// {
//     std::ifstream blocksFile("blocks.dat", std::ios::binary);
//     std::ifstream usersFile("users.dat", std::ios::binary);
//     if (blocksFile.is_open() && usersFile.is_open())
//     {
//         std::cout << "Successfully loaded data from files.\n";
//     }
//     else
//     {
//         std::cout << "Failed to load data from files.\n";
//     }
//     TransactionBlock block{};
//     blocksFile.read((char *)&block, sizeof(TransactionBlock));
//     while (!blocksFile.eof())
//     {
//         std::cout << block.id << " " << block.prevBlockId << " " << block.prevBlockHash << " " << block.validTransactions << std::endl;
//         blocksFile.read((char *)&block, sizeof(TransactionBlock));
//     }
//     blocksFile.close();
//     usersFile.close();
// }

void biggestBlocks(size_t count)
{
    std::ifstream blocksFile("../files/blocks.dat", std::ios::binary);
    if (blocksFile.is_open())
    {
        std::cout << "Successfully loaded data from files.\n";
    }
    else
    {
        std::cout << "Failed to load data from files.\n";
    }
    TransactionBlock block{};
    blocksFile.read((char *)&block, sizeof(TransactionBlock));
    while (!blocksFile.eof())
    {
        std::cout << block.id << " " << block.prevBlockId << " " << block.prevBlockHash << " " << block.validTransactions << std::endl;
        blocksFile.read((char *)&block, sizeof(TransactionBlock));
    }
    blocksFile.close();
}