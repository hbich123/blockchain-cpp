/**
 * @file sha256.cpp
 * @brief Implementation of SHA-256 cryptographic hash function
 */

#include "crypto/sha256.h"
#include <cstring>
#include <vector>

namespace crypto {

// Initialize K constants
constexpr uint32_t SHA256::K[64];

SHA256::SHA256() {
    // Initialize hash values (first 32 bits of fractional parts of square roots of first 8 primes)
    h[0] = 0x6a09e667;
    h[1] = 0xbb67ae85;
    h[2] = 0x3c6ef372;
    h[3] = 0xa54ff53a;
    h[4] = 0x510e527f;
    h[5] = 0x9b05688c;
    h[6] = 0x1f83d9ab;
    h[7] = 0x5be0cd19;
}

void SHA256::transform(const uint8_t* data) {
    uint32_t w[64];
    uint32_t a, b, c, d, e, f, g, h_temp;
    uint32_t t1, t2;
    
    // Prepare message schedule
    for (int i = 0; i < 16; i++) {
        w[i] = (data[i * 4] << 24) | (data[i * 4 + 1] << 16) | 
               (data[i * 4 + 2] << 8) | (data[i * 4 + 3]);
    }
    
    for (int i = 16; i < 64; i++) {
        w[i] = gamma1(w[i - 2]) + w[i - 7] + gamma0(w[i - 15]) + w[i - 16];
    }
    
    // Initialize working variables
    a = h[0];
    b = h[1];
    c = h[2];
    d = h[3];
    e = h[4];
    f = h[5];
    g = h[6];
    h_temp = h[7];
    
    // Main compression loop
    for (int i = 0; i < 64; i++) {
        t1 = h_temp + sigma1(e) + ch(e, f, g) + K[i] + w[i];
        t2 = sigma0(a) + maj(a, b, c);
        h_temp = g;
        g = f;
        f = e;
        e = d + t1;
        d = c;
        c = b;
        b = a;
        a = t1 + t2;
    }
    
    // Add compressed chunk to current hash value
    h[0] += a;
    h[1] += b;
    h[2] += c;
    h[3] += d;
    h[4] += e;
    h[5] += f;
    h[6] += g;
    h[7] += h_temp;
}

void SHA256::update(const uint8_t* data, size_t length) {
    for (size_t i = 0; i < length; i += 64) {
        size_t blockSize = (length - i >= 64) ? 64 : length - i;
        if (blockSize == 64) {
            transform(data + i);
        }
    }
}

std::string SHA256::finalize() {
    std::stringstream ss;
    for (int i = 0; i < 8; i++) {
        ss << std::hex << std::setfill('0') << std::setw(8) << h[i];
    }
    return ss.str();
}

std::string SHA256::hash(const std::string& input) {
    SHA256 sha;
    
    std::vector<uint8_t> data(input.begin(), input.end());
    
    // Pre-processing: adding padding bits
    size_t originalLength = data.size();
    size_t bitLength = originalLength * 8;
    
    // Append '1' bit (plus 0's)
    data.push_back(0x80);
    
    // Append 0's until message length ≡ 448 (mod 512)
    while ((data.size() % 64) != 56) {
        data.push_back(0x00);
    }
    
    // Append length as 64-bit big-endian integer
    for (int i = 7; i >= 0; i--) {
        data.push_back((bitLength >> (i * 8)) & 0xFF);
    }
    
    // Process each 512-bit chunk
    for (size_t i = 0; i < data.size(); i += 64) {
        sha.transform(data.data() + i);
    }
    
    return sha.finalize();
}

} // namespace crypto