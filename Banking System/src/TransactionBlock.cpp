#include "../headers/Bank.h"
#include "../headers/User.h"
#include "../headers/Transaction.h"
#include "../headers/TransactionBlock.h"
#include <iostream>
#include <fstream>

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

const uint16_t TransactionBlock::getValidTransactions() const {
    return validTransactions;
}

const uint16_t TransactionBlock::getTransactionID() const {
    return transactionID;
}

const uint16_t TransactionBlock::getPrevBlockId() const {
    return prevBlockId;
}

const uint16_t TransactionBlock::getPrevBlockHash() const {
    return prevBlockHash;
}

void TransactionBlock::setTransactionID(uint16_t transactionID) {
    this->transactionID = transactionID;
}

void TransactionBlock::setPrevBlockId(uint16_t prevBlockId) {
    this->prevBlockId = prevBlockId;
}

void TransactionBlock::setPrevBlockHash(uint16_t prevBlockHash) {
    this->prevBlockHash = prevBlockHash;
}

void TransactionBlock::setValidTransactions(uint16_t validTransactions) {
    this->validTransactions = validTransactions;
}

void TransactionBlock::printBlockInformation() const {
    std::cout << "Transaction Block ID: " << transactionID <<       "\n";
    std::cout << "Previous Block ID: "    << prevBlockId <<         "\n";
    std::cout << "Previous Block Hash: "  << prevBlockHash <<       "\n";
    std::cout << "Valid Transactions: "   << validTransactions <<   "\n";
}
