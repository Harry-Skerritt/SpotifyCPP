cmake_minimum_required(VERSION 3.20)
project(SpotifyAPILib VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)



# Library
add_library(SpotifyAPILib STATIC
        src/Auth.cpp
        src/AuthServer.cpp
        src/Tools.cpp
)

# Public includes: SpotifyAPILib
target_include_directories(SpotifyAPILib PUBLIC include)

# Private include: Thirdparty
target_include_directories(SpotifyAPILib PRIVATE thirdparty)

# Dependencies
find_package(CURL REQUIRED)
find_package(Threads REQUIRED) # For httplib

target_link_libraries(SpotifyAPILib PRIVATE
        CURL::libcurl
        Threads::Threads
)


# Examples (Test)
add_executable(example_authManual examples/authManualExample.cpp)
target_link_libraries(example_authManual PRIVATE SpotifyAPILib)

add_executable(example_authServer examples/authServerExample.cpp)
target_link_libraries(example_authServer PRIVATE SpotifyAPILib)

