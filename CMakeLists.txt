cmake_minimum_required(VERSION 3.7)
project(wordseg)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_COMPILER clang++-mp-4.0)

include_directories(./)
set(SOURCE_FILES test.cc)
add_executable(wordseg ${SOURCE_FILES})
add_executable(trie test_trie.cc)
