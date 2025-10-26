/**
 * @file proof_of_stake.cpp
 * @brief Implementation of Proof of Stake
 */

#include "consensus/proof_of_stake.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

namespace blockchain {
namespace consensus {

ProofOfStake::ProofOfStake() : gen(rd()) {}

int ProofOfStake::getTotalStake() const {
    int total = 0;
    for (const auto& validator : validators) {
        total += validator.stake;
    }
    return total;
}

bool ProofOfStake::addValidator(const std::string& name, int stake) {
    if (stake <= 0) {
        std::cerr << "Error: Stake must be positive" << std::endl;
        return false;
    }
    
    // Check if validator already exists
    for (const auto& v : validators) {
        if (v.name == name) {
            std::cerr << "Error: Validator already exists" << std::endl;
            return false;
        }
    }
    
    validators.emplace_back(name, stake);
    return true;
}

bool ProofOfStake::removeValidator(const std::string& name) {
    auto it = std::remove_if(validators.begin(), validators.end(),
        [&name](const Validator& v) { return v.name == name; });
    
    if (it != validators.end()) {
        validators.erase(it, validators.end());
        return true;
    }
    
    return false;
}

std::string ProofOfStake::selectValidator() {
    if (validators.empty()) {
        return "NoValidator";
    }
    
    int totalStake = getTotalStake();
    
    // Generate random number between 0 and totalStake
    std::uniform_int_distribution<> dis(0, totalStake - 1);
    int randomValue = dis(gen);
    
    // Select validator based on weighted probability
    int cumulative = 0;
    for (const auto& validator : validators) {
        cumulative += validator.stake;
        if (randomValue < cumulative) {
            return validator.name;
        }
    }
    
    // Fallback (should not reach here)
    return validators[0].name;
}

bool ProofOfStake::validateBlock(const std::string& validatorName) {
    // Check if validator exists
    for (const auto& v : validators) {
        if (v.name == validatorName) {
            return true;
        }
    }
    return false;
}

const Validator* ProofOfStake::getValidator(const std::string& name) const {
    for (const auto& v : validators) {
        if (v.name == name) {
            return &v;
        }
    }
    return nullptr;
}

void ProofOfStake::displayValidators() const {
    std::cout << "\n╔════════════════════════════════════════╗" << std::endl;
    std::cout << "║         VALIDATORS (PoS)               ║" << std::endl;
    std::cout << "╠════════════════════════════════════════╣" << std::endl;
    
    if (validators.empty()) {
        std::cout << "║  No validators registered              ║" << std::endl;
    } else {
        int totalStake = getTotalStake();
        for (const auto& v : validators) {
            double percentage = (v.stake * 100.0) / totalStake;
            std::cout << "║  " << std::left << std::setw(15) << v.name 
                      << " Stake: " << std::setw(6) << v.stake 
                      << " (" << std::fixed << std::setprecision(1) 
                      << percentage << "%)  ║" << std::endl;
        }
    }
    
    std::cout << "╚════════════════════════════════════════╝" << std::endl;
}

void ProofOfStake::displayStats() const {
    std::cout << "\n╔════════════════════════════════════════╗" << std::endl;
    std::cout << "║    PROOF OF STAKE STATISTICS           ║" << std::endl;
    std::cout << "╠════════════════════════════════════════╣" << std::endl;
    std::cout << "║ Total Validators: " << validators.size() << "                ║" << std::endl;
    std::cout << "║ Total Stake: " << getTotalStake() << " coins                 ║" << std::endl;
    std::cout << "╚════════════════════════════════════════╝" << std::endl;
}

} // namespace consensus
} // namespace blockchain