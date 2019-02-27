cmake_minimum_required(VERSION 3.8.0)

project (ch6_read_ir)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})

set(CH6_BUILD_ROOT ${CMAKE_CURRENT_BINARY_DIR})

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${LLVM_CMAKE_DIR})

include(AddLLVM)

set(LLVM_LINK_COMPONENTS
    BitReader
    Core
    Support)

add_executable(ch6_read_ir
  ch6_read_ir.cpp)

llvm_config(ch6_read_ir ${LLVM_LINK_COMPONENTS})

add_subdirectory(test)
