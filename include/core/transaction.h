/**
 * @file transaction.h
 * @brief Transaction class for blockchain
 * @author Blockchain Project
 * @date 2025
 */

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>

namespace blockchain {

/**
 * @class Transaction
 * @brief Represents a single transaction in the blockchain
 * 
 * A transaction records the transfer of value from one party to another.
 * Each transaction includes:
 * - Unique identifier
 * - Sender address
 * - Receiver address
 * - Amount being transferred
 * - Timestamp
 */
class Transaction {
private:
    std::string id;          ///< Unique transaction identifier
    std::string sender;      ///< Sender's address
    std::string receiver;    ///< Receiver's address
    double amount;           ///< Amount being transferred
    time_t timestamp;        ///< Transaction creation time
    
    /**
     * @brief Generate unique transaction ID
     * @return Generated ID string
     */
    std::string generateId();

public:
    /**
     * @brief Construct a new Transaction
     * @param sender Sender's address
     * @param receiver Receiver's address
     * @param amount Amount to transfer
     */
    Transaction(const std::string& sender, 
                const std::string& receiver, 
                double amount);
    
    /**
     * @brief Convert transaction to string representation
     * @return String representation of transaction
     */
    std::string toString() const;
    
    /**
     * @brief Calculate hash of transaction
     * @return SHA-256 hash of transaction data
     */
    std::string getHash() const;
    
    /**
     * @brief Display transaction details
     */
    void display() const;
    
    /**
     * @brief Validate transaction
     * @return true if transaction is valid
     */
    bool isValid() const;
    
    // Getters
    std::string getId() const { return id; }
    std::string getSender() const { return sender; }
    std::string getReceiver() const { return receiver; }
    double getAmount() const { return amount; }
    time_t getTimestamp() const { return timestamp; }
};

} // namespace blockchain

#endif // TRANSACTION_H