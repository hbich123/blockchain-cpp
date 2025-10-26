/**
 * @file merkle_tree.cpp
 * @brief Implementation of Merkle Tree
 */

#include "core/merkle_tree.h"
#include "crypto/sha256.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

namespace blockchain {

MerkleTree::MerkleTree(const std::vector<Transaction>& transactions) {
    if (transactions.empty()) {
        root = "0000000000000000000000000000000000000000000000000000000000000000";
        return;
    }
    
    // Hash each transaction to create leaves
    for (const auto& tx : transactions) {
        leaves.push_back(tx.getHash());
    }
    
    root = buildTreeIterative(leaves);
}

MerkleTree::MerkleTree(const std::vector<std::string>& transactionHashes) {
    if (transactionHashes.empty()) {
        root = "0000000000000000000000000000000000000000000000000000000000000000";
        return;
    }
    
    leaves = transactionHashes;
    root = buildTreeIterative(leaves);
}

std::string MerkleTree::buildTreeIterative(std::vector<std::string> nodes) {
    if (nodes.empty()) {
        return "0000000000000000000000000000000000000000000000000000000000000000";
    }
    
    if (nodes.size() == 1) {
        return nodes[0];
    }
    
    std::vector<std::string> currentLevel = nodes;
    
    // Build tree level by level until we reach the root
    while (currentLevel.size() > 1) {
        // If odd number of nodes, duplicate the last one
        if (currentLevel.size() % 2 != 0) {
            currentLevel.push_back(currentLevel.back());
        }
        
        std::vector<std::string> nextLevel;
        
        // Combine pairs of nodes
        for (size_t i = 0; i < currentLevel.size(); i += 2) {
            std::string combined = currentLevel[i] + currentLevel[i + 1];
            nextLevel.push_back(crypto::sha256(combined));
        }
        
        currentLevel = nextLevel;
    }
    
    return currentLevel[0];
}

void MerkleTree::display() const {
    std::cout << "\n╔════════════════════════════════════════╗" << std::endl;
    std::cout << "║         MERKLE TREE                    ║" << std::endl;
    std::cout << "╠════════════════════════════════════════╣" << std::endl;
    std::cout << "║ Leaves: " << std::setw(31) << std::left << leaves.size() << "║" << std::endl;
    std::cout << "║ Root: " << root.substr(0, 32) << "║" << std::endl;
    std::cout << "╚════════════════════════════════════════╝" << std::endl;
}

bool MerkleTree::verifyTransaction(const std::string& transactionHash) const {
    return std::find(leaves.begin(), leaves.end(), transactionHash) != leaves.end();
}

} // namespace blockchain