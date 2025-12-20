cmake_minimum_required(VERSION 3.20)
project(SpotifyAPILib VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Library
add_library(SpotifyAPILib STATIC
        src/Auth.cpp
        src/Tools.cpp
)

target_include_directories(SpotifyAPILib PUBLIC include)

# Dependencies
find_package(CURL REQUIRED)
target_link_libraries(SpotifyAPILib PRIVATE CURL::libcurl)


# Examples (Test)
add_executable(example_test examples/example.cpp)
target_link_libraries(example_test PRIVATE SpotifyAPILib)
