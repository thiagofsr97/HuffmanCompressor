cmake_minimum_required(VERSION 3.7)
project(Huffman)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Node.h Node.cpp Huffman.h Huffman.cpp FileIO.h FileIO.cpp)
add_executable(Huffman ${SOURCE_FILES})