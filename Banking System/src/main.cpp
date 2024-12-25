#include <iostream>
#include <fstream>
#include <cstring>

#include "../headers/user.h"
#include "../headers/run.h"
#include "../headers/transaction.h"

int main()
{
    std::fstream blocksFile("blocks.dat", std::ios::binary | std::ios::app | std::ios::in | std::ios::out);
    std::fstream usersFile("users.dat", std::ios::binary | std::ios::app | std::ios::in | std::ios::out);
    if (!blocksFile.is_open() && !usersFile.is_open())
    {
        std::cout << "Failed to load data from files in main().\n";
    }
    else
    {
        std::cout << "Successfully loaded data from files in main().\n";
    }

    menu();
    char command[128];
    while (true)
    {
        std::cin.getline(command, sizeof(command));

        if (strcmp(command, "create-user") == 0)
        {
            createUser(usersFile, blocksFile);
        }
        else if (strcmp(command, "print") == 0)
        {
            printUsers(usersFile);
        }
        else if (strcmp(command, "print-users-coins") == 0)
        {
            printUsersCoins(usersFile, blocksFile);
        }
        else if (strcmp(command, "delete-user") == 0)
        {
            deleteUser();
        }
        //        else if (strcmp(command, "make-transaction") == 0)
        //        {
        //            char senderName[128];
        //            char receiverName[128];
        //            size_t amount;
        //            std::cin >> senderName >> receiverName >> amount;
        //            User sender = createUser(senderName, 0);
        //            User receiver = createUser(receiverName, 0);
        //            makeTransaction(sender, receiver, moneyToOOPCoin(amount));
        //        }
        //        else if (strcmp(command, "verify-transactions") == 0)
        //        {
        //            verifyTransactions();
        //        }
        //        else if (strcmp(command, "wealthiest-users") == 0)
        //        {
        //            size_t count;
        //            std::cin >> count;
        //            printWealthiestUsers(count);
        //        }
        //        else if (strcmp(command, "biggest-blocks") == 0)
        //        {
        //            size_t count;
        //            std::cin >> count;
        //            biggestBlocks(count);
        //        }
        else if (strcmp(command, "exit") == 0)
        {
            break;
        }
    }
    return 0;
}
