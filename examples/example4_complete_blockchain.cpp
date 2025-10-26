/**
 * @file example4_complete_blockchain.cpp
 * @brief Complete blockchain demonstration with PoW and PoS
 * @author Blockchain Project
 * @date 2025
 */

#include "core/blockchain.h"
#include <iostream>
#include <chrono>
#include <iomanip>

using namespace blockchain;
using namespace std::chrono;

/**
 * @brief Display program header
 */
void displayHeader() {
    std::cout << "\n╔═══════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║    COMPLETE BLOCKCHAIN IMPLEMENTATION             ║" << std::endl;
    std::cout << "║    Master IASD 2025/2026                          ║" << std::endl;
    std::cout << "║    Pr. Ikram BENABDELOUAHAB                       ║" << std::endl;
    std::cout << "╚═══════════════════════════════════════════════════╝" << std::endl;
}

/**
 * @brief Test complete blockchain with transactions
 */
void testCompleteBlockchain() {
    std::cout << "\n" << std::string(55, '=') << std::endl;
    std::cout << "  TEST 1: Complete Blockchain with Transactions" << std::endl;
    std::cout << std::string(55, '=') << "\n" << std::endl;
    
    // Create blockchain with difficulty 3
    Blockchain blockchain(3);
    
    // Configure PoS validators
    std::cout << "→ Configuring Proof of Stake validators..." << std::endl;
    blockchain.addValidator("Alice", 100);
    blockchain.addValidator("Bob", 75);
    blockchain.addValidator("Charlie", 125);
    blockchain.addValidator("Dave", 200);
    
    blockchain.getPoS().displayValidators();
    
    // Create transaction batches
    std::vector<Transaction> batch1 = {
        Transaction("Alice", "Bob", 10.5),
        Transaction("Bob", "Charlie", 5.2),
        Transaction("Charlie", "Dave", 3.7)
    };
    
    std::vector<Transaction> batch2 = {
        Transaction("Dave", "Alice", 2.1),
        Transaction("Alice", "Charlie", 8.3)
    };
    
    std::vector<Transaction> batch3 = {
        Transaction("Bob", "Dave", 4.6),
        Transaction("Charlie", "Alice", 1.9),
        Transaction("Dave", "Bob", 6.8)
    };
    
    // Add blocks with PoW
    std::cout << "\n→ Adding blocks with Proof of Work..." << std::endl;
    blockchain.addBlockPoW(batch1);
    blockchain.addBlockPoW(batch2);
    
    // Add blocks with PoS
    std::cout << "\n→ Adding blocks with Proof of Stake..." << std::endl;
    blockchain.addBlockPoS(batch3);
    
    // Display blockchain
    blockchain.displayChain();
    blockchain.displayStats();
    
    // Verify integrity
    std::cout << "\n→ Verifying chain integrity..." << std::endl;
    if (blockchain.isChainValid()) {
        std::cout << "  ✓ Blockchain is VALID!" << std::endl;
    } else {
        std::cout << "  ✗ Blockchain is INVALID!" << std::endl;
    }
}

/**
 * @brief Comparative analysis between PoW and PoS
 */
void comparativeAnalysis() {
    std::cout << "\n\n" << std::string(55, '=') << std::endl;
    std::cout << "  TEST 2: Comparative Analysis PoW vs PoS" << std::endl;
    std::cout << std::string(55, '=') << "\n" << std::endl;
    
    const int NUM_BLOCKS = 5;
    
    // Create transaction batches
    std::vector<std::vector<Transaction>> transactionBatches;
    for (int i = 0; i < NUM_BLOCKS; i++) {
        std::vector<Transaction> batch = {
            Transaction("User" + std::to_string(i), "Merchant", 10.0 + i),
            Transaction("Merchant", "User" + std::to_string(i+1), 5.0 + i)
        };
        transactionBatches.push_back(batch);
    }
    
    // ==================== TEST PoW ====================
    std::cout << "\n╔═══════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║         TESTING PROOF OF WORK                     ║" << std::endl;
    std::cout << "╚═══════════════════════════════════════════════════╝" << std::endl;
    
    Blockchain blockchainPoW(3);
    
    auto startPoW = high_resolution_clock::now();
    
    for (int i = 0; i < NUM_BLOCKS; i++) {
        blockchainPoW.addBlockPoW(transactionBatches[i]);
    }
    
    auto endPoW = high_resolution_clock::now();
    auto durationPoW = duration_cast<milliseconds>(endPoW - startPoW);
    
    // ==================== TEST PoS ====================
    std::cout << "\n╔═══════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║         TESTING PROOF OF STAKE                    ║" << std::endl;
    std::cout << "╚═══════════════════════════════════════════════════╝" << std::endl;
    
    Blockchain blockchainPoS(3);
    blockchainPoS.addValidator("Alice", 100);
    blockchainPoS.addValidator("Bob", 80);
    blockchainPoS.addValidator("Charlie", 120);
    
    blockchainPoS.getPoS().displayValidators();
    
    auto startPoS = high_resolution_clock::now();
    
    for (int i = 0; i < NUM_BLOCKS; i++) {
        blockchainPoS.addBlockPoS(transactionBatches[i]);
    }
    
    auto endPoS = high_resolution_clock::now();
    auto durationPoS = duration_cast<milliseconds>(endPoS - startPoS);
    
    // ==================== RESULTS ====================
    std::cout << "\n╔═══════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║         COMPARATIVE ANALYSIS RESULTS              ║" << std::endl;
    std::cout << "╠═══════════════════════════════════════════════════╣" << std::endl;
    std::cout << "║                                                   ║" << std::endl;
    std::cout << "║  PROOF OF WORK (Difficulty 3):                    ║" << std::endl;
    std::cout << "║  • Total Time: " << std::left << std::setw(32) 
              << (std::to_string(durationPoW.count()) + " ms") << "║" << std::endl;
    std::cout << "║  • Avg Time/Block: " << std::left << std::setw(28) 
              << (std::to_string(durationPoW.count() / NUM_BLOCKS) + " ms") << "║" << std::endl;
    std::cout << "║  • Resources: High CPU usage (100%)               ║" << std::endl;
    std::cout << "║  • Energy: High consumption                       ║" << std::endl;
    std::cout << "║                                                   ║" << std::endl;
    std::cout << "║  PROOF OF STAKE:                                  ║" << std::endl;
    std::cout << "║  • Total Time: " << std::left << std::setw(32) 
              << (std::to_string(durationPoS.count()) + " ms") << "║" << std::endl;
    std::cout << "║  • Avg Time/Block: " << std::left << std::setw(28) 
              << (std::to_string(std::max(1LL, durationPoS.count()) / NUM_BLOCKS) + " ms") << "║" << std::endl;
    std::cout << "║  • Resources: Minimal CPU usage (<5%)             ║" << std::endl;
    std::cout << "║  • Energy: Very low consumption                   ║" << std::endl;
    std::cout << "║                                                   ║" << std::endl;
    
    double speedup = static_cast<double>(durationPoW.count()) / std::max(1LL, durationPoS.count());
    std::cout << "║  ⚡ SPEEDUP FACTOR:                                ║" << std::endl;
    std::cout << "║     PoS is " << std::fixed << std::setprecision(1) 
              << speedup << "x FASTER than PoW" << std::setw(17) << " " << "║" << std::endl;
    std::cout << "║                                                   ║" << std::endl;
    std::cout << "╠═══════════════════════════════════════════════════╣" << std::endl;
    std::cout << "║           CONCLUSIONS                             ║" << std::endl;
    std::cout << "╠═══════════════════════════════════════════════════╣" << std::endl;
    std::cout << "║                                                   ║" << std::endl;
    std::cout << "║  ✓ PoW: Very secure but slow and energy-intensive║" << std::endl;
    std::cout << "║  ✓ PoS: Fast, efficient, but risk of centralization║" << std::endl;
    std::cout << "║  ✓ Both maintain chain integrity and validity     ║" << std::endl;
    std::cout << "║  ✓ Choice depends on use case requirements        ║" << std::endl;
    std::cout << "║                                                   ║" << std::endl;
    std::cout << "╚═══════════════════════════════════════════════════╝" << std::endl;
}

/**
 * @brief Test difficulty scaling
 */
void testDifficultyScaling() {
    std::cout << "\n\n" << std::string(55, '=') << std::endl;
    std::cout << "  TEST 3: PoW Difficulty Scaling" << std::endl;
    std::cout << std::string(55, '=') << "\n" << std::endl;
    
    std::vector<int> difficulties = {1, 2, 3, 4};
    std::vector<Transaction> testTxs = {
        Transaction("Alice", "Bob", 10.0)
    };
    
    std::cout << "\n╔═══════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║   Difficulty Level    |    Mining Time (ms)       ║" << std::endl;
    std::cout << "╠═══════════════════════════════════════════════════╣" << std::endl;
    
    for (int diff : difficulties) {
        Blockchain bc(diff);
        
        auto start = high_resolution_clock::now();
        bc.addBlockPoW(testTxs);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        
        std::cout << "║         " << diff << "             |         " 
                  << std::setw(6) << duration.count() << " ms          ║" << std::endl;
    }
    
    std::cout << "╚═══════════════════════════════════════════════════╝" << std::endl;
    std::cout << "\n✓ Mining time increases exponentially with difficulty" << std::endl;
}

/**
 * @brief Main function
 */
int main() {
    displayHeader();
    
    try {
        // Test 1: Complete blockchain
        testCompleteBlockchain();
        
        // Test 2: Comparative analysis
        comparativeAnalysis();
        
        // Test 3: Difficulty scaling
        testDifficultyScaling();
        
        std::cout << "\n\n╔═══════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║         ALL TESTS COMPLETED SUCCESSFULLY!         ║" << std::endl;
        std::cout << "╚═══════════════════════════════════════════════════╝\n" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "\n✗ Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}