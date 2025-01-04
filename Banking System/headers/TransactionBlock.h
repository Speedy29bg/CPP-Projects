
#ifndef TRANSACTIONBLOCK_H
#define TRANSACTIONBLOCK_H

#include <cstdint>

class TransactionBlock
{
private:
    uint16_t transactionID;
    uint16_t prevBlockId;
    uint16_t prevBlockHash;
    uint16_t validTransactions;

public:
    TransactionBlock() =  default;
    ~TransactionBlock() = default;
    TransactionBlock(unsigned transactionID,
                     unsigned prevBlockId,
                     unsigned prevBlockHash,
                     uint16_t validTransactions);

    const uint16_t getTransactionID()    const;
    const uint16_t getPrevBlockId()      const;
    const uint16_t getPrevBlockHash()    const;
    const uint16_t getValidTransactions()const;

    void setTransactionID(uint16_t id);
    void setPrevBlockId(uint16_t id);
    void setPrevBlockHash(uint16_t id);
    void setValidTransactions(uint16_t validTransactions);

    void printBlockInformation()         const;
};


#endif //TRANSACTIONBLOCK_H
