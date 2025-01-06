#include "TransactionBlock.h"

/**
 * Constructs a TransactionBlock object with the given parameters.
 *
 * @param transactionID The unique identifier for this transaction block.
 * @param prevBlockId The ID of the previous block in the blockchain.
 * @param prevBlockHash The hash of the previous block in the blockchain.
 * @param validTransactions The number of valid transactions included in this block.
 *                           Must be greater than zero; otherwise, an exception is thrown.
 *
 * @throws std::invalid_argument If validTransactions is zero.
 */
TransactionBlock::TransactionBlock(uint16_t transactionID,
                                   uint16_t prevBlockId,
                                   uint16_t prevBlockHash,
                                   uint16_t validTransactions)
    : transactionID(transactionID),
      prevBlockId(prevBlockId),
      prevBlockHash(prevBlockHash),
      validTransactions(validTransactions) {
    if (validTransactions == 0) {
        throw std::invalid_argument("TransactionBlock cannot have zero valid transactions.");
    }
}

/**
 * Sets the transaction ID for this transaction block.
 *
 * This method assigns a new transaction ID to the block after verifying
 * that the ID is not zero. If a zero ID is provided, an exception is thrown.
 *
 * @param id The transaction ID to be set. Must be a non-zero value.
 * @throws std::invalid_argument if the provided id is zero.
 */
void TransactionBlock::setTransactionID(uint16_t id) {
    if (id == 0) {
        throw std::invalid_argument("Transaction ID cannot be zero.");
    }
    transactionID = id;
}

/**
 * Sets the ID of the previous block in the chain.
 *
 * @param id The ID of the previous block. Must be a non-zero value.
 * @throws std::invalid_argument if the provided ID is zero.
 */
void TransactionBlock::setPrevBlockId(uint16_t id) {
    if (id == 0) {
        throw std::invalid_argument("Previous block ID cannot be zero.");
    }
    prevBlockId = id;
}

/**
 * Sets the hash of the previous transaction block.
 *
 * @param id The hash ID of the previous block. Must be non-zero.
 * @throws std::invalid_argument if the provided hash ID is zero.
 */
void TransactionBlock::setPrevBlockHash(uint16_t id) {
    if (id == 0) {
        throw std::invalid_argument("Previous block hash cannot be zero.");
    }
    prevBlockHash = id;
}

/**
 * Sets the number of valid transactions for the transaction block.
 *
 * @param count The number of valid transactions to set. Must be greater than zero.
 * @throws std::invalid_argument if count is zero.
 */
void TransactionBlock::setValidTransactions(uint16_t count) {
    if (count == 0) {
        throw std::invalid_argument("Valid transactions count cannot be zero.");
    }
    validTransactions = count;
}

/**
 * @brief Prints the details of the transaction block to the console.
 *
 * This method outputs the following information to the console:
 * - Transaction ID: The unique identifier for the transaction block.
 * - Previous Block ID: The ID of the block that precedes this block in the chain.
 * - Previous Block Hash: The hash value of the previous block.
 * - Valid Transactions: The number of valid transactions contained within this block.
 *
 * It provides a concise summary of the block's properties, which can be used
 * for debugging, logging, or informational purposes.
 */
void TransactionBlock::printBlockInformation() const {
    std::cout << "Transaction Block Information:\n";
    std::cout << "  Transaction ID: " << transactionID << "\n";
    std::cout << "  Previous Block ID: " << prevBlockId << "\n";
    std::cout << "  Previous Block Hash: " << prevBlockHash << "\n";
    std::cout << "  Valid Transactions: " << validTransactions << "\n";
}