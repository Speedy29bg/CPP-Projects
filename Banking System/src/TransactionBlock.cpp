#include "../headers/Bank.h"
#include "../headers/User.h"
#include "../headers/Transaction.h"
#include "../headers/TransactionBlock.h"
#include <iostream>
#include <fstream>

/**
 * @brief Constructs a TransactionBlock object and initializes its members.
 *
 * @param id The unique identifier for the transaction block.
 * @param prevBlockId The unique identifier of the previous block in the chain.
 * @param prevBlockHash The hash value of the previous block in the chain.
 * @param validTransactions The number of valid transactions included in this block.
 *
 * @return A constructed TransactionBlock object with initialized member variables.
 */
TransactionBlock::TransactionBlock(unsigned id,
                                   unsigned prevBlockId,
                                   unsigned prevBlockHash,
                                   uint16_t validTransactions)
{
    this->transactionID = id;
    this->prevBlockId = prevBlockId;
    this->prevBlockHash = prevBlockHash;
    this->validTransactions = validTransactions;
}

/**
 * Retrieves the number of valid transactions within the transaction block.
 *
 * @return The number of valid transactions as a 16-bit unsigned integer.
 */
const uint16_t TransactionBlock::getValidTransactions() const {
    return validTransactions;
}

/**
 * Retrieves the transaction ID of the current TransactionBlock instance.
 *
 * @return The transaction ID as an unsigned 16-bit integer.
 */
const uint16_t TransactionBlock::getTransactionID() const {
    return transactionID;
}

/**
 * Retrieves the ID of the previous block in the blockchain sequence.
 *
 * @return The ID of the previous block as an unsigned 16-bit integer.
 */
const uint16_t TransactionBlock::getPrevBlockId() const {
    return prevBlockId;
}

/**
 * Retrieves the hash of the previous block in the chain.
 *
 * @return The 16-bit unsigned integer representing the hash of the previous block.
 */
const uint16_t TransactionBlock::getPrevBlockHash() const {
    return prevBlockHash;
}

/**
 * Sets the transaction ID for the transaction block.
 *
 * @param transactionID The unique identifier for the transaction.
 */
void TransactionBlock::setTransactionID(uint16_t transactionID) {
    this->transactionID = transactionID;
}

/**
 * @brief Sets the identifier of the previous block.
 *
 * This method updates the ID of the block that precedes
 * the current transaction block in the blockchain.
 *
 * @param prevBlockId The new identifier for the previous block.
 */
void TransactionBlock::setPrevBlockId(uint16_t prevBlockId) {
    this->prevBlockId = prevBlockId;
}

/**
 * @brief Sets the hash of the previous block for the current transaction block.
 *
 * @param prevBlockHash The hash value of the previous block.
 */
void TransactionBlock::setPrevBlockHash(uint16_t prevBlockHash) {
    this->prevBlockHash = prevBlockHash;
}

/**
 * Sets the number of valid transactions for the transaction block.
 *
 * @param validTransactions The number of valid transactions to be set, represented as a 16-bit unsigned integer.
 */
void TransactionBlock::setValidTransactions(uint16_t validTransactions) {
    this->validTransactions = validTransactions;
}

/**
 * @brief Prints the information about the transaction block.
 *
 * This method displays details of the transaction block, including:
 * - The transaction block ID.
 * - The ID of the previous block in the chain.
 * - The hash value of the previous block.
 * - The total number of valid transactions in the block.
 *
 * The output is sent to the standard output stream (console).
 */
void TransactionBlock::printBlockInformation() const {
    std::cout << "Transaction Block ID: " << transactionID <<       "\n";
    std::cout << "Previous Block ID: "    << prevBlockId <<         "\n";
    std::cout << "Previous Block Hash: "  << prevBlockHash <<       "\n";
    std::cout << "Valid Transactions: "   << validTransactions <<   "\n";
}
