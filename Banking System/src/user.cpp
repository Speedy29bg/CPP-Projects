#include <iostream>
#include <fstream>
#include <cstring>
#include "../headers/user.h"
#include "../headers/transaction.h"

void createUser(std::fstream &usersFile, std::fstream &blocksFile)
{
    User user;
    char name[128];
    double moneyForDeposit;
    std::cout << "Enter name of user: ";
    std::cin.getline(name, sizeof(name));
    strcpy(user.name, name);
    std::cout << "Enter money for deposit: ";
    std::cin >> moneyForDeposit;

    usersFile.seekg(0, std::ios::end);
    size_t numberOfUsers = usersFile.tellg() / sizeof(User);
    user.id = numberOfUsers;
    usersFile.seekg(0, std::ios::beg);

    usersFile.write((char *)&user, sizeof(User));
    std::cout << "Successfully created user " << user.name << " with id " << user.id << ".\n";
    makeTransaction(usersFile, blocksFile, systemUser, user, moneyToOOPCoin(moneyForDeposit));
}

// void printUsersCoins(User user)
// {
//     std::ifstream blocksFileRead("blocks.dat", std::ios::binary);
//     if (!blocksFileRead.is_open())
//     {
//         std::cout << "Failed to load data from files.\n";
//     }
//     else
//     {
//         std::cout << "Successfully loaded data from files.\n";
//     }
//     TransactionBlock block{};
//     blocksFileRead.seekg(0, std::ios::end);
//     size_t numberOfBlocks = blocksFileRead.tellg() / sizeof(TransactionBlock);
//     blocksFileRead.seekg(0, std::ios::beg);
//     blocksFileRead.read((char *)&block, sizeof(TransactionBlock));
//     size_t coins = 0;
//     while (!blocksFileRead.eof())
//     {
//         for (int i = 0; i < block.validTransactions; ++i)
//         {
//             if (block.transactions[i].sender == user.id)
//             {
//                 coins -= block.transactions[i].coins;
//             }
//             else if (block.transactions[i].receiver == user.id)
//             {
//                 coins += block.transactions[i].coins;
//             }
//         }
//         blocksFileRead.read((char *)&block, sizeof(TransactionBlock));
//     }
//     std::cout << "User " << user.name << " has " << coins << " coins.\n";
//     blocksFileRead.close();
// }
static void deleteUserFromUsersFile(unsigned id)
{
    std::ifstream usersFileRead("users.dat", std::ios::binary);
    std::ofstream usersFile("users.dat", std::ios::binary);
    if (usersFile.is_open() && usersFileRead.is_open())
    {
        std::cout << "Successfully loaded data from files.\n";
    }
    else
    {
        std::cout << "Failed to load data from files.\n";
    }
    User user{};
    usersFileRead.seekg(0, std::ios::end);
    usersFileRead.seekg(0, std::ios::beg);
    usersFileRead.read((char *)&user, sizeof(User));
    while (!usersFileRead.eof())
    {
        if (user.id != id)
        {
            usersFile.write((char *)&user, sizeof(User));
        }
        usersFileRead.read((char *)&user, sizeof(User));
    }
    usersFileRead.close();
    usersFile.close();
}
static void deleteUserFromBlocksFile(unsigned id)
{
    std::ifstream blocksFileRead("../files/blocks.dat", std::ios::binary);
    std::ofstream blocksFile("../files/blocks.dat", std::ios::binary);
    if (blocksFile.is_open() && blocksFileRead.is_open())
    {
        std::cout << "Successfully loaded data from files.\n";
    }
    else
    {
        std::cout << "Failed to load data from files.\n";
    }
    TransactionBlock block{};
    blocksFileRead.seekg(0, std::ios::end);
    blocksFileRead.seekg(0, std::ios::beg);
    blocksFileRead.read((char *)&block, sizeof(TransactionBlock));
    while (!blocksFileRead.eof())
    {
        for (int i = 0; i < block.validTransactions; ++i)
        {
            if (block.transactions[i].sender != id && block.transactions[i].receiver != id)
            {
                blocksFile.write((char *)&block, sizeof(TransactionBlock));
            }
        }
        blocksFileRead.read((char *)&block, sizeof(TransactionBlock));
    }
    blocksFileRead.close();
    blocksFile.close();
}
static User findUser(unsigned id)
{
    std::ifstream usersFileRead("../files/users.dat", std::ios::binary);
    if (usersFileRead.is_open())
    {
        std::cout << "Successfully loaded data from files.\n";
    }
    else
    {
        std::cout << "Failed to load data from files.\n";
    }
    User user{};
    usersFileRead.seekg(0, std::ios::end);
    size_t numberOfUsers = usersFileRead.tellg() / sizeof(User);
    usersFileRead.seekg(0, std::ios::beg);
    usersFileRead.read((char *)&user, sizeof(User));
    while (!usersFileRead.eof())
    {
        if (user.id == id)
        {
            return user;
        }
        usersFileRead.read((char *)&user, sizeof(User));
    }
    usersFileRead.close();
    return user;
}
void deleteUser()
{
    unsigned id;
    std::cout << "Enter id of user to delete: ";
    std::cin >> id;
    deleteUserFromUsersFile(id);
    deleteUserFromBlocksFile(id);
}

void printUsersCoins(std::fstream &usersFile, std::fstream &blocksFile)
{
    if (!usersFile.is_open() || !blocksFile.is_open())
    {
        std::cout << "Failed to load data from files.\n";
    }
    else
    {
        std::cout << "Successfully loaded data from files.\n";
    }
    User user{};
    Transaction transaction{};

    usersFile.seekp(0, std::ios::beg);
    while (usersFile.read((char *)&user, sizeof(User)))
    {
        double coins = 0;
        blocksFile.seekp(0, std::ios::beg);
        while (blocksFile.read((char *)&transaction, sizeof(Transaction)))
        {
            if (transaction.sender == user.id)
            {
                coins -= transaction.coins;
            }
            else if (transaction.receiver == user.id)
            {
                coins += transaction.coins;
            }
        }
        std::cout << "User: " << user.name << " with ID: " << user.id << " has " << coins << " coins.\n";
    }
    usersFile.clear();
    blocksFile.clear();
}
void printUsers(std::fstream &usersFile)
{
    if (!usersFile.is_open())
    {
        std::cout << "Failed to load data from files.\n";
    }
    else
    {
        std::cout << "Successfully loaded data from files.\n";
    }
    User user{};
    usersFile.seekp(0, std::ios::beg);
    while (usersFile.read((char *)&user, sizeof(User)))
    {
        std::cout << "User: " << user.name << " with ID: " << user.id << std::endl;
    }
    usersFile.clear();
}
void printBlocks(std::fstream &blocksFile)
{
    if (!blocksFile.is_open())
    {
        std::cout << "Failed to load data from files.\n";
    }
    else
    {
        std::cout << "Successfully loaded data from files.\n";
    }
    TransactionBlock block{};
    blocksFile.seekp(0, std::ios::beg);
    while (blocksFile.read((char *)&block, sizeof(TransactionBlock)))
    {
        std::cout << "Block: " << block.id << " with " << block.validTransactions << " transactions." << std::endl;
    }
    blocksFile.clear();
}
// void printWealthiestUsers(size_t count)
// {
//     std::ifstream usersFileRead("../files/users.dat", std::ios::binary);
//     std::ifstream blocksFileRead("../files/blocks.dat", std::ios::binary);
//     if (usersFileRead.is_open() && blocksFileRead.is_open())
//     {
//         std::cout << "Successfully loaded data from files.\n";
//     }
//     else
//     {
//         std::cout << "Failed to load data from files.\n";
//     }
//     User user{};
//     TransactionBlock block{};
//     size_t *wealth;
//     wealth = new size_t[count];
//     for (int i = 0; i < count; ++i)
//     {
//         wealth[i] = 0;
//     }
//     usersFileRead.seekg(0, std::ios::end);
//     size_t numberOfUsers = usersFileRead.tellg() / sizeof(User);
//     usersFileRead.seekg(0, std::ios::beg);
//     usersFileRead.read((char *)&user, sizeof(User));
//     while (!usersFileRead.eof())
//     {
//         blocksFileRead.seekg(0, std::ios::beg);
//         blocksFileRead.read((char *)&block, sizeof(TransactionBlock));
//         while (!blocksFileRead.eof())
//         {
//             for (int i = 0; i < block.validTransactions; ++i)
//             {
//                 if (block.transactions[i].sender == user.id)
//                 {
//                     wealth[user.id] -= block.transactions[i].coins;
//                 }
//                 if (block.transactions[i].receiver == user.id)
//                 {
//                     wealth[user.id] += block.transactions[i].coins;
//                 }
//             }
//             blocksFileRead.read((char *)&block, sizeof(TransactionBlock));
//         }
//         usersFileRead.read((char *)&user, sizeof(User));
//     }
//     for (int i = 0; i < count; ++i)
//     {
//         for (int j = 0; j < numberOfUsers; ++j)
//         {
//             usersFileRead.seekg(j * sizeof(User));
//             usersFileRead.read((char *)&user, sizeof(User));
//             if (wealth[user.id] > wealth[i])
//             {
//                 swapWealth(user.id, i);
//             }
//         }
//     }
//     for (int i = 0; i < count; ++i)
//     {
//         for (int j = 0; j < numberOfUsers; ++j)
//         {
//             usersFileRead.seekg(j * sizeof(User));
//             usersFileRead.read((char *)&user, sizeof(User));
//             if (user.id == i)
//             {
//                 printUserInfoFromFile(usersFileRead, user);
//             }
//         }
//     }
//     usersFileRead.close();
//     blocksFileRead.close();
//     delete[] wealth;
// }
// void printTransactionsOfUser(unsigned id)
// {
//     std::ifstream usersFileRead("users.dat", std::ios::binary);
//     std::ifstream blocksFileRead("blocks.dat", std::ios::binary);
//     if (usersFileRead.is_open() && blocksFileRead.is_open())
//     {
//         std::cout << "Successfully loaded data from files.\n";
//     }
//     else
//     {
//         std::cout << "Failed to load data from files.\n";
//     }
//     User user{};
//     TransactionBlock block{};
//     usersFileRead.seekg(0, std::ios::end);
//     size_t numberOfUsers = usersFileRead.tellg() / sizeof(User);
//     usersFileRead.seekg(0, std::ios::beg);
//     usersFileRead.read((char *)&user, sizeof(User));
//     while (!usersFileRead.eof())
//     {
//         if (user.id == id)
//         {
//             printUserInfoFromFile(usersFileRead, user);
//         }
//         usersFileRead.read((char *)&user, sizeof(User));
//     }
//     blocksFileRead.seekg(0, std::ios::beg);
//     blocksFileRead.read((char *)&block, sizeof(TransactionBlock));
//     while (!blocksFileRead.eof())
//     {
//         for (int i = 0; i < block.validTransactions; ++i)
//         {
//             if (block.transactions[i].sender == id || block.transactions[i].receiver == id)
//             {
//                 std::cout << block.transactions[i].sender << " " << block.transactions[i].receiver << " " << block.transactions[i].coins << std::endl;
//             }
//         }
//         blocksFileRead.read((char *)&block, sizeof(TransactionBlock));
//     }
//     usersFileRead.close();
//     blocksFileRead.close();
// }
void swapWealth(unsigned id1, unsigned id2)
{
    std::ifstream usersFileRead("users.dat", std::ios::binary);
    std::ofstream usersFile("users.dat", std::ios::binary);
    if (usersFile.is_open() && usersFileRead.is_open())
    {
        std::cout << "Successfully loaded data from files.\n";
    }
    else
    {
        std::cout << "Failed to load data from files.\n";
    }
    User user1{}, user2{};
    usersFileRead.seekg(0, std::ios::end);
    size_t numberOfUsers = usersFileRead.tellg() / sizeof(User);
    usersFileRead.seekg(0, std::ios::beg);
    usersFileRead.read((char *)&user1, sizeof(User));
    while (!usersFileRead.eof())
    {
        if (user1.id == id1)
        {
            break;
        }
        usersFileRead.read((char *)&user1, sizeof(User));
    }
    usersFileRead.seekg(0, std::ios::beg);
    usersFileRead.read((char *)&user2, sizeof(User));
    while (!usersFileRead.eof())
    {
        if (user2.id == id2)
        {
            break;
        }
        usersFileRead.read((char *)&user2, sizeof(User));
    }
    usersFileRead.seekg(0, std::ios::beg);
    usersFileRead.read((char *)&user1, sizeof(User));
    while (!usersFileRead.eof())
    {
        if (user1.id == id1)
        {
            usersFile.write((char *)&user2, sizeof(User));
        }
        else if (user1.id == id2)
        {
            usersFile.write((char *)&user1, sizeof(User));
        }
        else
        {
            usersFile.write((char *)&user1, sizeof(User));
        }
        usersFileRead.read((char *)&user1, sizeof(User));
    }
    usersFileRead.close();
    usersFile.close();
}