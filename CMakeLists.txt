cmake_minimum_required(VERSION 3.10)
project(AdaCLI)

set(CMAKE_CXX_STANDARD 17)

# Project headers
include_directories(include)

# Crypto++ headers
include_directories(/usr/include/cryptopp)

# Source files
file(GLOB SOURCES "src/*.cpp")

# Build executable
add_executable(ada ${SOURCES})

# Link Crypto++ library
target_link_libraries(ada cryptopp)