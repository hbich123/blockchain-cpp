# blockchain-cpp
# 🔗 Mini Blockchain Implementation in C++

A complete, production-ready blockchain implementation in C++ featuring Merkle Trees, Proof of Work (PoW), and Proof of Stake (PoS) consensus mechanisms.

## 🎯 Features

- ✅ **Merkle Tree Implementation** - Efficient transaction verification
- ✅ **Proof of Work (PoW)** - Mining with adjustable difficulty
- ✅ **Proof of Stake (PoS)** - Energy-efficient consensus mechanism
- ✅ **SHA-256 Hashing** - Cryptographically secure hash function
- ✅ **Transaction System** - Complete transaction management
- ✅ **Chain Validation** - Integrity verification
- ✅ **Modular Architecture** - Clean separation of concerns
- ✅ **Performance Metrics** - Built-in benchmarking tools

## 🏗️ Architecture

```
┌─────────────────────────────────────────┐
│           Blockchain Layer              │
├─────────────────────────────────────────┤
│  Block Management | Chain Validation    │
└─────────────────────────────────────────┘
           │                    │
    ┌──────┴──────┐      ┌─────┴──────┐
    │   Consensus │      │    Core    │
    ├─────────────┤      ├────────────┤
    │ PoW  │  PoS │      │ Merkle Tree│
    └─────────────┘      │ Transaction│
                         └────────────┘
```

## 🚀 Quick Start

### Prerequisites

- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.10+
- Git

### Installation

```bash
# Clone the repository
git clone https://github.com/yourusername/blockchain-cpp.git
cd blockchain-cpp

# Create build directory
mkdir build && cd build

# Configure and build
cmake ..
make

# Run examples
./example4_complete_blockchain
```

### Windows (MinGW)

```bash
g++ -std=c++17 -I include src/**/*.cpp examples/example4_complete_blockchain.cpp -o blockchain
blockchain.exe
```

### Windows (Visual Studio)

```bash
cmake -G "Visual Studio 16 2019" ..
cmake --build . --config Release
```

## 📚 Usage Examples

### Example 1: Merkle Tree

```cpp
#include "core/merkle_tree.h"

int main() {
    std::vector<std::string> transactions = {
        "Alice -> Bob: 10 BTC",
        "Bob -> Charlie: 5 BTC"
    };
    
    MerkleTree tree(transactions);
    std::cout << "Merkle Root: " << tree.getRoot() << std::endl;
    
    return 0;
}
```

### Example 2: Proof of Work

```cpp
#include "core/blockchain.h"
#include "consensus/proof_of_work.h"

int main() {
    Blockchain blockchain(3); // difficulty = 3
    
    std::vector<Transaction> txs = {
        Transaction("Alice", "Bob", 10.0)
    };
    
    blockchain.addBlockPoW(txs);
    
    std::cout << "Chain valid: " << blockchain.isChainValid() << std::endl;
    
    return 0;
}
```

### Example 3: Proof of Stake

```cpp
#include "core/blockchain.h"
#include "consensus/proof_of_stake.h"

int main() {
    Blockchain blockchain(3);
    
    blockchain.addValidator("Alice", 100);
    blockchain.addValidator("Bob", 200);
    
    std::vector<Transaction> txs = {
        Transaction("Alice", "Bob", 10.0)
    };
    
    blockchain.addBlockPoS(txs);
    
    return 0;
}
```

## 🔬 Performance Comparison

| Metric | Proof of Work | Proof of Stake |
|--------|---------------|----------------|
| Block Time | 50-500ms | 1-5ms |
| CPU Usage | High (100%) | Low (<5%) |
| Energy | High | Very Low |
| Security | Computational | Economic |
| **Speed Factor** | 1x | **100-500x faster** |

## 📖 API Documentation

### Core Classes

#### `Transaction`
```cpp
Transaction(const std::string& sender, 
           const std::string& receiver, 
           double amount);
```

#### `Block`
```cpp
Block(int index, 
     const std::string& previousHash, 
     const std::vector<Transaction>& transactions);
     
void mineBlock(int difficulty);
void validateBlock(const std::string& validator);
```

#### `Blockchain`
```cpp
Blockchain(int difficulty = 3);

void addBlockPoW(const std::vector<Transaction>& transactions);
void addBlockPoS(const std::vector<Transaction>& transactions);
bool isChainValid() const;
```

## 🧪 Running Tests

```bash
cd build
./test_blockchain
```

## 📊 Project Structure

- **`include/`** - Header files organized by module
- **`src/`** - Implementation files
- **`examples/`** - Demonstration programs
- **`tests/`** - Unit tests
- **`docs/`** - Additional documentation

## 🔐 Security Considerations

- ✅ Uses SHA-256 for cryptographic hashing
- ✅ Validates chain integrity on every operation
- ✅ Prevents tampering through cryptographic linking
- ⚠️ **Note**: This is an educational implementation. For production use, consider:
  - Network layer implementation
  - Persistent storage
  - Advanced consensus mechanisms
  - Formal security audit

## 🤝 Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 👨‍🎓 Academic Context

This project was developed as part of the Master IASD (Intelligence Artificielle et Science des Données) program at [Your University], under the supervision of Pr. Ikram BENABDELOUAHAB.

**Course**: Blockchain Technology  
**Year**: 2025/2026  
**Workshop**: Complete Implementation of a Simplified Blockchain

## 📚 References

- [Bitcoin Whitepaper](https://bitcoin.org/bitcoin.pdf) - Satoshi Nakamoto
- [Ethereum Yellow Paper](https://ethereum.github.io/yellowpaper/paper.pdf)
- [Merkle Trees Explained](https://brilliant.org/wiki/merkle-tree/)
- [Proof of Work vs Proof of Stake](https://ethereum.org/en/developers/docs/consensus-mechanisms/)

## 🙋‍♂️ Authors

- **Hbich Soufiane** 

## 🌟 Acknowledgments

- Professor Ikram BENABDELOUAHAB for the guidance
- The blockchain community for inspiration
- Contributors and testers

---

⭐ **Star this repository if you find it helpful!**

📧 **Contact**: ahbichepro123@gmail.com
