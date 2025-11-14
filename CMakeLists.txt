cmake_minimum_required(VERSION 3.10)
project(AdaCLI)

set(CMAKE_CXX_STANDARD 17)

# Project headers
include_directories(include)

# Crypto++ headers
include_directories(/usr/include/cryptopp)

# Source files
file(GLOB SOURCES "src/*.cpp")

# Find packages
find_package(CURL REQUIRED)
find_package(nlohmann_json QUIET)

# Build executable
add_executable(ada ${SOURCES})

# Link libraries
target_link_libraries(ada cryptopp)
target_link_libraries(ada CURL::libcurl)

# If nlohmann_json is found, link it; otherwise we'll use a header-only approach
if(nlohmann_json_FOUND)
    target_link_libraries(ada nlohmann_json::nlohmann_json)
endif()