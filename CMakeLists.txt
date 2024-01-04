cmake_minimum_required(VERSION 3.24)

project(MerkleExample
        DESCRIPTION "Example project implementing Merkle trees"
        VERSION 0.1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)


add_subdirectory(external)
add_subdirectory(MerkleLib)
add_subdirectory(tests)