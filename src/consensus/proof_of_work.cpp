/**
 * @file proof_of_work.cpp
 * @brief Implementation of Proof of Work
 */

#include "consensus/proof_of_work.h"
#include "crypto/sha256.h"
#include <iostream>
#include <sstream>

namespace blockchain {
namespace consensus {

ProofOfWork::ProofOfWork(int difficulty) 
    : difficulty(difficulty), miningTime(0) {
    target = std::string(difficulty, '0');
}

std::string ProofOfWork::mine(const std::string& data, int& nonce) {
    std::string hash;
    nonce = 0;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    // Keep incrementing nonce until we find a valid hash
    do {
        std::stringstream ss;
        ss << data << nonce;
        hash = crypto::sha256(ss.str());
        nonce++;
    } while (!validateHash(hash));
    
    auto end = std::chrono::high_resolution_clock::now();
    miningTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    
    return hash;
}

bool ProofOfWork::validateHash(const std::string& hash) const {
    return hash.substr(0, difficulty) == target;
}

void ProofOfWork::setDifficulty(int newDifficulty) {
    if (newDifficulty < 1 || newDifficulty > 8) {
        std::cerr << "Warning: Difficulty should be between 1 and 8" << std::endl;
        return;
    }
    difficulty = newDifficulty;
    target = std::string(difficulty, '0');
}

void ProofOfWork::displayStats() const {
    std::cout << "\n╔════════════════════════════════════════╗" << std::endl;
    std::cout << "║      PROOF OF WORK STATISTICS          ║" << std::endl;
    std::cout << "╠════════════════════════════════════════╣" << std::endl;
    std::cout << "║ Difficulty: " << difficulty << "                          ║" << std::endl;
    std::cout << "║ Target: " << target << "...                     ║" << std::endl;
    std::cout << "║ Last Mining Time: " << miningTime << " ms               ║" << std::endl;
    std::cout << "╚════════════════════════════════════════╝" << std::endl;
}

} // namespace consensus
} // namespace blockchain