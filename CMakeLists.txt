cmake_minimum_required(VERSION 3.20)
project(SpotifyAPILib VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)



# --- Library ---
add_library(SpotifyAPILib STATIC
        src/Auth.cpp
        src/AuthServer.cpp
        src/Tools.cpp
)

# Public includes: SpotifyAPILib
target_include_directories(SpotifyAPILib PUBLIC include)

# Private include: Thirdparty
target_include_directories(SpotifyAPILib PRIVATE thirdparty)

# --- Dependencies ---
find_package(CURL REQUIRED)
find_package(Threads REQUIRED) # For httplib

target_link_libraries(SpotifyAPILib PRIVATE
        CURL::libcurl
        Threads::Threads
)


# --- Examples ---
# --- Helper to put binaries in the right subfolder ---
function(set_example_output_dir TARGET_NAME SUBFOLDER)
    set_target_properties(${TARGET_NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples/${SUBFOLDER}"
    )
    # Handle Multi-config (Debug/Release folders) for macOS/Windows
    foreach(CONFIG ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER ${CONFIG} CONFIG_UPPER)
        set_target_properties(${TARGET_NAME} PROPERTIES
                RUNTIME_OUTPUT_DIRECTORY_${CONFIG_UPPER} "${CMAKE_BINARY_DIR}/examples/${SUBFOLDER}"
        )
    endforeach()
endfunction()

# --- Auth Examples ---
add_executable(example_authManual examples/auth/authManualExample.cpp)
target_link_libraries(example_authManual PRIVATE SpotifyAPILib)
set_example_output_dir(example_authManual "auth")

add_executable(example_authServer examples/auth/authServerExample.cpp)
target_link_libraries(example_authServer PRIVATE SpotifyAPILib)
set_example_output_dir(example_authServer "auth")



#Copy the HTML file to the same folder as the binaries
configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/examples/auth/index.html"
        "${CMAKE_BINARY_DIR}/examples/auth/index.html"
        COPYONLY
)

# --- X Examples ---

