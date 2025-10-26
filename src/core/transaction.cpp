/**
 * @file transaction.cpp
 * @brief Implementation of Transaction class
 */

#include "core/transaction.h"
#include "crypto/sha256.h"
#include <sstream>
#include <iomanip>
#include <iostream>

namespace blockchain {

Transaction::Transaction(const std::string& sender, 
                        const std::string& receiver, 
                        double amount)
    : sender(sender), receiver(receiver), amount(amount) {
    timestamp = std::time(nullptr);
    id = generateId();
}

std::string Transaction::generateId() {
    std::stringstream ss;
    ss << sender << receiver << amount << timestamp;
    std::string hash = crypto::sha256(ss.str());
    return hash.substr(0, 16); // Use first 16 characters as ID
}

std::string Transaction::toString() const {
    std::stringstream ss;
    ss << id << ":" << sender << "->" << receiver << ":" 
       << std::fixed << std::setprecision(8) << amount;
    return ss.str();
}

std::string Transaction::getHash() const {
    return crypto::sha256(toString());
}

void Transaction::display() const {
    std::cout << "  [" << id << "] " 
              << sender << " → " << receiver 
              << " : " << std::fixed << std::setprecision(8) 
              << amount << " BTC" << std::endl;
}

bool Transaction::isValid() const {
    // Basic validation rules
    if (sender.empty() || receiver.empty()) {
        return false;
    }
    
    if (amount <= 0) {
        return false;
    }
    
    if (sender == receiver) {
        return false;
    }
    
    return true;
}

} // namespace blockchain