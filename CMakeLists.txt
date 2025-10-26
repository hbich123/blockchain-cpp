cmake_minimum_required(VERSION 3.10)
project(BlockchainCPP VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source files
set(CRYPTO_SOURCES
    src/crypto/sha256.cpp
)

set(CORE_SOURCES
    src/core/transaction.cpp
    src/core/merkle_tree.cpp
    src/core/block.cpp
    src/core/blockchain.cpp
)

set(CONSENSUS_SOURCES
    src/consensus/proof_of_work.cpp
    src/consensus/proof_of_stake.cpp
)

set(ALL_SOURCES
    ${CRYPTO_SOURCES}
    ${CORE_SOURCES}
    ${CONSENSUS_SOURCES}
)

# Create library
add_library(blockchain_lib STATIC ${ALL_SOURCES})

# Examples
add_executable(example1_merkle_tree examples/example1_merkle_tree.cpp)
target_link_libraries(example1_merkle_tree blockchain_lib)

add_executable(example2_proof_of_work examples/example2_proof_of_work.cpp)
target_link_libraries(example2_proof_of_work blockchain_lib)

add_executable(example3_proof_of_stake examples/example3_proof_of_stake.cpp)
target_link_libraries(example3_proof_of_stake blockchain_lib)

add_executable(example4_complete_blockchain examples/example4_complete_blockchain.cpp)
target_link_libraries(example4_complete_blockchain blockchain_lib)

# Tests
add_executable(test_blockchain tests/test_blockchain.cpp)
target_link_libraries(test_blockchain blockchain_lib)

# Installation
install(TARGETS blockchain_lib DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)

# Print build information
message(STATUS "Blockchain C++ Project Configuration:")
message(STATUS "  Version: ${PROJECT_VERSION}")
message(STATUS "  C++ Standard: C++${CMAKE_CXX_STANDARD}")
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "")
message(STATUS "Build targets:")
message(STATUS "  blockchain_lib - Static library")
message(STATUS "  example1_merkle_tree - Merkle Tree demo")
message(STATUS "  example2_proof_of_work - PoW demo")
message(STATUS "  example3_proof_of_stake - PoS demo")
message(STATUS "  example4_complete_blockchain - Complete blockchain demo")
message(STATUS "  test_blockchain - Test suite")