/**
 * @file block.h
 * @brief Block structure for blockchain
 * @author Blockchain Project
 * @date 2025
 */

#ifndef BLOCK_H
#define BLOCK_H

#include "core/transaction.h"
#include "core/merkle_tree.h"
#include <vector>
#include <string>
#include <ctime>

namespace blockchain {

/**
 * @enum ConsensusType
 * @brief Type of consensus used for block validation
 */
enum class ConsensusType {
    NONE,          ///< No consensus (genesis block)
    PROOF_OF_WORK, ///< Proof of Work
    PROOF_OF_STAKE ///< Proof of Stake
};

/**
 * @class Block
 * @brief Represents a block in the blockchain
 * 
 * A block contains:
 * - Index (position in chain)
 * - Timestamp
 * - Previous block hash
 * - Merkle root of transactions
 * - Nonce (for PoW)
 * - Current block hash
 * - List of transactions
 * - Consensus information
 */
class Block {
private:
    int index;                              ///< Block index in chain
    time_t timestamp;                       ///< Block creation time
    std::string previousHash;               ///< Hash of previous block
    std::string merkleRoot;                 ///< Merkle root of transactions
    int nonce;                              ///< Nonce for PoW
    std::string hash;                       ///< Current block hash
    std::vector<Transaction> transactions;  ///< Transactions in block
    ConsensusType consensusType;            ///< Consensus mechanism used
    std::string validator;                  ///< Validator name (for PoS)
    
    /**
     * @brief Calculate hash of block
     * @return SHA-256 hash of block data
     */
    std::string calculateHash() const;

public:
    /**
     * @brief Construct a new Block
     * @param index Block index
     * @param previousHash Hash of previous block
     * @param transactions Vector of transactions
     */
    Block(int index, 
          const std::string& previousHash, 
          const std::vector<Transaction>& transactions);
    
    /**
     * @brief Mine block using Proof of Work
     * @param difficulty Number of leading zeros required
     * @return Mining time in milliseconds
     */
    long long mineBlock(int difficulty);
    
    /**
     * @brief Validate block using Proof of Stake
     * @param validatorName Name of validator
     * @return Validation time in microseconds
     */
    long long validateBlock(const std::string& validatorName);
    
    /**
     * @brief Display block information
     */
    void display() const;
    
    /**
     * @brief Check if block is valid
     * @param difficulty PoW difficulty (if applicable)
     * @return true if block is valid
     */
    bool isValid(int difficulty = 0) const;
    
    // Getters
    int getIndex() const { return index; }
    std::string getHash() const { return hash; }
    std::string getPreviousHash() const { return previousHash; }
    std::string getMerkleRoot() const { return merkleRoot; }
    int getNonce() const { return nonce; }
    time_t getTimestamp() const { return timestamp; }
    ConsensusType getConsensusType() const { return consensusType; }
    std::string getValidator() const { return validator; }
    const std::vector<Transaction>& getTransactions() const { return transactions; }
};

} // namespace blockchain

#endif // BLOCK_H