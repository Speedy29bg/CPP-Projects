cmake_minimum_required(VERSION 3.30)
project(CPP_Projects)

set(CMAKE_CXX_STANDARD 14)

include_directories("Banking System")
include_directories("Banking System/headers")
include_directories("Banking System/src")

add_executable(CPP_Projects
        "Banking System/headers/transaction.h"
    "Banking System/headers/user.h"
    "Banking System/src/blocks.dat"
    "Banking System/src/main.cpp"
        "Banking System/src/transaction.cpp"
    "Banking System/src/user.cpp"
    "Banking System/src/users.dat"
        "Banking System/src/Bank.cpp"
        "Banking System/headers/Bank.h"
        "Banking System/src/TransactionBlock.cpp"
        "Banking System/headers/TransactionBlock.h")
