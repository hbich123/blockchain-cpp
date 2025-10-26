/**
 * @file merkle_tree.h
 * @brief Merkle Tree implementation for transaction verification
 * @author Blockchain Project
 * @date 2025
 */

#ifndef MERKLE_TREE_H
#define MERKLE_TREE_H

#include "core/transaction.h"
#include <vector>
#include <string>

namespace blockchain {

/**
 * @class MerkleTree
 * @brief Implements a Merkle Tree for efficient transaction verification
 * 
 * A Merkle Tree is a binary tree where:
 * - Leaf nodes contain hashes of transactions
 * - Internal nodes contain hashes of their children
 * - The root hash represents all transactions
 * 
 * Benefits:
 * - Efficient verification of transaction inclusion
 * - Tamper detection
 * - Reduced storage requirements for SPV clients
 * 
 * @note Uses iterative approach for better performance and stack safety
 */
class MerkleTree {
private:
    std::vector<std::string> leaves;  ///< Transaction hashes (leaf nodes)
    std::string root;                 ///< Merkle root hash
    
    /**
     * @brief Build tree iteratively from leaf nodes to root
     * @param nodes Initial leaf nodes
     * @return Root hash
     */
    std::string buildTreeIterative(std::vector<std::string> nodes);

public:
    /**
     * @brief Construct Merkle Tree from transactions
     * @param transactions Vector of transactions
     */
    explicit MerkleTree(const std::vector<Transaction>& transactions);
    
    /**
     * @brief Construct Merkle Tree from transaction hashes
     * @param transactionHashes Vector of pre-computed hashes
     */
    explicit MerkleTree(const std::vector<std::string>& transactionHashes);
    
    /**
     * @brief Get Merkle root hash
     * @return Root hash as hex string
     */
    std::string getRoot() const { return root; }
    
    /**
     * @brief Get leaf hashes
     * @return Vector of leaf node hashes
     */
    const std::vector<std::string>& getLeaves() const { return leaves; }
    
    /**
     * @brief Display tree information
     */
    void display() const;
    
    /**
     * @brief Verify if a transaction is in the tree
     * @param transactionHash Hash of transaction to verify
     * @return true if transaction is in tree
     */
    bool verifyTransaction(const std::string& transactionHash) const;
};

} // namespace blockchain

#endif // MERKLE_TREE_H