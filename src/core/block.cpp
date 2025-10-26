/**
 * @file block.cpp
 * @brief Implementation of Block class
 */

#include "core/block.h"
#include "crypto/sha256.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <chrono>

namespace blockchain {

Block::Block(int index, 
             const std::string& previousHash, 
             const std::vector<Transaction>& transactions)
    : index(index), previousHash(previousHash), transactions(transactions),
      nonce(0), consensusType(ConsensusType::NONE), validator("") {
    
    timestamp = std::time(nullptr);
    
    // Calculate Merkle root
    MerkleTree merkleTree(transactions);
    merkleRoot = merkleTree.getRoot();
    
    // Calculate initial hash
    hash = calculateHash();
}

std::string Block::calculateHash() const {
    std::stringstream ss;
    ss << index << timestamp << previousHash << merkleRoot << nonce << validator;
    return crypto::sha256(ss.str());
}

long long Block::mineBlock(int difficulty) {
    consensusType = ConsensusType::PROOF_OF_WORK;
    std::string target(difficulty, '0');
    
    auto start = std::chrono::high_resolution_clock::now();
    
    // Find valid nonce
    while (hash.substr(0, difficulty) != target) {
        nonce++;
        hash = calculateHash();
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
    std::cout << "  ✓ Block #" << index << " mined (PoW) | Nonce: " << nonce 
              << " | Time: " << duration.count() << " ms" << std::endl;
    
    return duration.count();
}

long long Block::validateBlock(const std::string& validatorName) {
    consensusType = ConsensusType::PROOF_OF_STAKE;
    validator = validatorName;
    nonce = 0;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    hash = calculateHash();
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "  ✓ Block #" << index << " validated (PoS) | Validator: " << validator 
              << " | Time: " << duration.count() << " µs" << std::endl;
    
    return duration.count();
}

void Block::display() const {
    std::cout << "\n╔═══════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  BLOCK #" << std::left << std::setw(42) << index << "║" << std::endl;
    std::cout << "╠═══════════════════════════════════════════════════╣" << std::endl;
    
    // Consensus type
    std::string consensusStr;
    switch (consensusType) {
        case ConsensusType::NONE: consensusStr = "None (Genesis)"; break;
        case ConsensusType::PROOF_OF_WORK: consensusStr = "Proof of Work"; break;
        case ConsensusType::PROOF_OF_STAKE: consensusStr = "Proof of Stake"; break;
    }
    std::cout << "║ Consensus: " << std::left << std::setw(40) << consensusStr << "║" << std::endl;
    
    // PoS specific
    if (consensusType == ConsensusType::PROOF_OF_STAKE) {
        std::cout << "║ Validator: " << std::left << std::setw(40) << validator << "║" << std::endl;
    }
    
    // PoW specific
    if (consensusType == ConsensusType::PROOF_OF_WORK) {
        std::cout << "║ Nonce: " << std::left << std::setw(44) << nonce << "║" << std::endl;
    }
    
    // Common fields
    std::cout << "║ Previous Hash: " << previousHash.substr(0, 34) << "║" << std::endl;
    std::cout << "║ Merkle Root: " << merkleRoot.substr(0, 36) << "║" << std::endl;
    std::cout << "║ Block Hash: " << hash.substr(0, 37) << "║" << std::endl;
    std::cout << "║ Transactions: " << std::left << std::setw(36) << transactions.size() << "║" << std::endl;
    
    // Timestamp
    char timeStr[26];
    struct tm* timeInfo = std::localtime(&timestamp);
    std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", timeInfo);
    std::cout << "║ Timestamp: " << std::left << std::setw(39) << timeStr << "║" << std::endl;
    
    std::cout << "╚═══════════════════════════════════════════════════╝" << std::endl;
    
    // Display transactions
    if (!transactions.empty()) {
        std::cout << "Transactions in block:" << std::endl;
        for (const auto& tx : transactions) {
            tx.display();
        }
    }
}

bool Block::isValid(int difficulty) const {
    // Check if hash is correct
    if (hash != calculateHash()) {
        return false;
    }
    
    // For PoW, check difficulty
    if (consensusType == ConsensusType::PROOF_OF_WORK && difficulty > 0) {
        std::string target(difficulty, '0');
        if (hash.substr(0, difficulty) != target) {
            return false;
        }
    }
    
    // Validate all transactions
    for (const auto& tx : transactions) {
        if (!tx.isValid()) {
            return false;
        }
    }
    
    return true;
}

} // namespace blockchain