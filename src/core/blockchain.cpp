/**
 * @file blockchain.cpp
 * @brief Implementation of Blockchain class
 */

#include "core/blockchain.h"
#include <iostream>
#include <iomanip>

namespace blockchain {

Blockchain::Blockchain(int difficulty) 
    : powDifficulty(difficulty), pow(difficulty) {
    // Create and add genesis block
    Block genesis = createGenesisBlock();
    genesis.validateBlock("System");
    chain.push_back(genesis);
}

Block Blockchain::createGenesisBlock() {
    std::vector<Transaction> genesisTxs;
    genesisTxs.push_back(Transaction("System", "Network", 0.0));
    return Block(0, "0000000000000000000000000000000000000000000000000000000000000000", genesisTxs);
}

bool Blockchain::addValidator(const std::string& name, int stake) {
    return pos.addValidator(name, stake);
}

bool Blockchain::addBlockPoW(const std::vector<Transaction>& transactions) {
    std::cout << "\n➤ Adding block with Proof of Work..." << std::endl;
    
    // Validate all transactions
    for (const auto& tx : transactions) {
        if (!tx.isValid()) {
            std::cerr << "  ✗ Error: Invalid transaction detected" << std::endl;
            return false;
        }
    }
    
    // Create new block
    Block newBlock(chain.size(), getLastBlock().getHash(), transactions);
    
    // Mine the block
    newBlock.mineBlock(powDifficulty);
    
    // Add to chain
    chain.push_back(newBlock);
    
    return true;
}

bool Blockchain::addBlockPoS(const std::vector<Transaction>& transactions) {
    std::cout << "\n➤ Adding block with Proof of Stake..." << std::endl;
    
    // Check if validators exist
    if (pos.getValidatorCount() == 0) {
        std::cerr << "  ✗ Error: No validators available" << std::endl;
        return false;
    }
    
    // Validate all transactions
    for (const auto& tx : transactions) {
        if (!tx.isValid()) {
            std::cerr << "  ✗ Error: Invalid transaction detected" << std::endl;
            return false;
        }
    }
    
    // Select validator
    std::string validator = pos.selectValidator();
    std::cout << "  → Validator selected: " << validator << std::endl;
    
    // Create new block
    Block newBlock(chain.size(), getLastBlock().getHash(), transactions);
    
    // Validate the block
    newBlock.validateBlock(validator);
    
    // Add to chain
    chain.push_back(newBlock);
    
    return true;
}

bool Blockchain::isChainValid() const {
    // Check each block (skip genesis)
    for (size_t i = 1; i < chain.size(); i++) {
        const Block& currentBlock = chain[i];
        const Block& previousBlock = chain[i - 1];
        
        // Verify block hash links
        if (currentBlock.getPreviousHash() != previousBlock.getHash()) {
            std::cerr << "✗ Error at block " << i << ": Previous hash mismatch" << std::endl;
            return false;
        }
        
        // Verify block validity
        if (!currentBlock.isValid(powDifficulty)) {
            std::cerr << "✗ Error at block " << i << ": Block is invalid" << std::endl;
            return false;
        }
        
        // For PoW blocks, verify difficulty
        if (currentBlock.getConsensusType() == ConsensusType::PROOF_OF_WORK) {
            std::string target(powDifficulty, '0');
            if (currentBlock.getHash().substr(0, powDifficulty) != target) {
                std::cerr << "✗ Error at block " << i << ": PoW difficulty not met" << std::endl;
                return false;
            }
        }
        
        // For PoS blocks, verify validator
        if (currentBlock.getConsensusType() == ConsensusType::PROOF_OF_STAKE) {
            if (!pos.validateBlock(currentBlock.getValidator())) {
                std::cerr << "✗ Error at block " << i << ": Invalid validator" << std::endl;
                return false;
            }
        }
    }
    
    return true;
}

const Block& Blockchain::getLastBlock() const {
    return chain.back();
}

const Block* Blockchain::getBlock(int index) const {
    if (index >= 0 && index < static_cast<int>(chain.size())) {
        return &chain[index];
    }
    return nullptr;
}

void Blockchain::setDifficulty(int difficulty) {
    if (difficulty < 1 || difficulty > 8) {
        std::cerr << "Warning: Difficulty should be between 1 and 8" << std::endl;
        return;
    }
    powDifficulty = difficulty;
    pow.setDifficulty(difficulty);
}

void Blockchain::displayChain() const {
    std::cout << "\n╔═══════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║              BLOCKCHAIN - " << chain.size() << " blocks" << std::setw(18) << " " << "║" << std::endl;
    std::cout << "╚═══════════════════════════════════════════════════╝" << std::endl;
    
    for (const auto& block : chain) {
        block.display();
    }
}

void Blockchain::displayStats() const {
    int powBlocks = 0;
    int posBlocks = 0;
    int totalTransactions = 0;
    
    for (const auto& block : chain) {
        if (block.getConsensusType() == ConsensusType::PROOF_OF_WORK) {
            powBlocks++;
        } else if (block.getConsensusType() == ConsensusType::PROOF_OF_STAKE) {
            posBlocks++;
        }
        totalTransactions += block.getTransactions().size();
    }
    
    std::cout << "\n╔═══════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║           BLOCKCHAIN STATISTICS                   ║" << std::endl;
    std::cout << "╠═══════════════════════════════════════════════════╣" << std::endl;
    std::cout << "║ Total Blocks: " << std::left << std::setw(35) << chain.size() << "║" << std::endl;
    std::cout << "║ PoW Blocks: " << std::left << std::setw(37) << powBlocks << "║" << std::endl;
    std::cout << "║ PoS Blocks: " << std::left << std::setw(37) << posBlocks << "║" << std::endl;
    std::cout << "║ Total Transactions: " << std::left << std::setw(29) << totalTransactions << "║" << std::endl;
    std::cout << "║ PoW Difficulty: " << std::left << std::setw(33) << powDifficulty << "║" << std::endl;
    std::cout << "║ Validators: " << std::left << std::setw(37) << pos.getValidatorCount() << "║" << std::endl;
    std::cout << "║ Chain Valid: " << std::left << std::setw(36) << (isChainValid() ? "YES ✓" : "NO ✗") << "║" << std::endl;
    std::cout << "╚═══════════════════════════════════════════════════╝" << std::endl;
}

} // namespace blockchain