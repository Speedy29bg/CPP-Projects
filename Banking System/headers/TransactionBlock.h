#pragma once

#include <cstdint>
#include <iostream>
#include <stdexcept>

/**
 * @class TransactionBlock
 * @brief Represents a block in a transaction chain with its associated metadata.
 *
 * The TransactionBlock class defines the structure and behavior of a block in a
 * blockchain-like system. It holds information such as transaction ID, previous
 * block ID, hash of the previous block, and the count of valid transactions in
 * the block.
 */
class TransactionBlock {
private:
    uint16_t transactionID {};         // Unique identifier for this transaction block
    uint16_t prevBlockId {};           // ID of the previous block in the chain
    uint16_t prevBlockHash {};         // Hash of the previous block
    uint16_t validTransactions {};     // Number of valid transactions in this block

public:
    // Default constructor
    TransactionBlock() = default;

    // Parameterized constructor
    TransactionBlock(uint16_t transactionID,
                     uint16_t prevBlockId,
                     uint16_t prevBlockHash,
                     uint16_t validTransactions);

    // Getters
    uint16_t getTransactionID() const { return transactionID; }
    uint16_t getPrevBlockId() const { return prevBlockId; }
    uint16_t getPrevBlockHash() const { return prevBlockHash; }
    uint16_t getValidTransactions() const { return validTransactions; }

    // Setters with validation
    void setTransactionID(uint16_t id);
    void setPrevBlockId(uint16_t id);
    void setPrevBlockHash(uint16_t id);
    void setValidTransactions(uint16_t count);

    // Print block information
    void printBlockInformation() const;

    ~TransactionBlock() = default; // Default destructor
};