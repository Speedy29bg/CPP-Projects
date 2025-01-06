#include <iostream>
#include "Bank.h"
#include "User.h"
#include "Transaction.h"
#include "TransactionBlock.h"

/**
 * @brief The main entry point of the application.
 *
 * This function initializes a banking system, performing operations like
 * adding users, conducting transactions, deleting users, and managing
 * transaction blocks. It demonstrates multiple functionalities of a Bank
 * system such as printing the wealthiest users, validating and displaying
 * transactions, and managing a blockchain of transaction blocks.
 *
 * The program handles exceptions for invalid transactions or errors
 * during execution, ensuring proper resource management and error reporting.
 *
 * @return Returns 0 upon successful execution, or other values in case of failure.
 */
int main() {
    try {
        // Create a bank
        Bank myBank;

        // Create some users
        User user1(1, "Alice", 500.0);
        User user2(2, "Bob", 300.0);
        User user3(3, "Charlie", 120.0);
        User user4(4, "Diana", 800.0);

        // Add users to the bank
        myBank.addUser(user1);
        myBank.addUser(user2);
        myBank.addUser(user3);
        myBank.addUser(user4);

        // Print initial wealthiest users
        std::cout << "\nInitial Wealthiest Users:\n";
        myBank.printWealthiestUsers(3);

        // Conduct some valid transactions
        std::cout << "\nConducting Transactions:\n";
        myBank.makeTransaction(user1, user2, 50.0); // Alice pays 50 to Bob
        myBank.makeTransaction(user4, user3, 100.0); // Diana pays 100 to Charlie

        // Print the wealthiest users after transactions
        std::cout << "\nWealthiest Users After Transactions:\n";
        myBank.printWealthiestUsers(3);

        // Attempt an invalid transaction (insufficient balance)
        std::cout << "\nAttempting Invalid Transaction:\n";
        try {
            myBank.makeTransaction(user3, user1, 500.0); // Charlie tries to send 500 coins to Alice
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }

        // Remove a user (e.g., Bob) from the bank
        std::cout << "\nRemoving User (Bob):\n";
        if (myBank.deleteUser("Bob")) {
            std::cout << "Bob has been removed from the bank.\n";
        } else {
            std::cout << "Bob could not be found in the bank.\n";
        }

        // Print all users after removal
        std::cout << "\nWealthiest Users After Removal:\n";
        myBank.printWealthiestUsers(10); // Print all users for clarity

        // Create a transaction block
        std::cout << "\nCreating and Displaying Transaction Block:\n";
        TransactionBlock block(1, 0, 0xbeaf, 2); // Initial transaction block
        block.printBlockInformation();

        // Modify block attributes and print again
        block.setValidTransactions(3);
        block.setPrevBlockHash(0xabcd);
        std::cout << "\nUpdated Transaction Block Information:\n";
        block.printBlockInformation();

        // Verify a transaction manually
        std::cout << "\nVerifying Manual Transaction:\n";
        Transaction customTransaction(user1, user2, 20.0, time(nullptr));
        if (customTransaction.verifyTransaction()) {
            std::cout << "Transaction verified successfully!\n";
            customTransaction.printTransactionInformation();
        } else {
            std::cout << "Transaction verification failed.\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}