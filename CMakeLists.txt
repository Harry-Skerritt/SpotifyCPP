cmake_minimum_required(VERSION 3.20)
project(SpotifyCPP VERSION 0.9.6 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# --- Options ---
# This allows users to build the library without examples by default
option(BUILD_EXAMPLES "Build the example applications" ON)

# --- Dependencies ---
find_package(CURL REQUIRED)
find_package(Threads REQUIRED)

# --- Library ---
add_library(SpotifyCPP STATIC
        src/auth/Auth.cpp
        src/auth/AuthServer.cpp
        src/core/Client.cpp
        src/util/Http.cpp
        src/util/Tools.cpp
        src/util/JsonMapping.cpp
        src/api/AlbumAPI.cpp
        src/api/ArtistAPI.cpp
        src/api/AudiobookAPI.cpp
        src/api/BaseAPI.cpp
        src/api/BrowseAPI.cpp
        src/api/CategoryAPI.cpp
        src/api/ChapterAPI.cpp
        src/api/EpisodeAPI.cpp
        src/api/PlayerAPI.cpp
        src/api/PlaylistAPI.cpp
        src/api/ShowsAPI.cpp
        src/api/TrackAPI.cpp
        src/api/UsersAPI.cpp
        src/extensions/VisualAPI.cpp
)

# Public includes: SpotifyCPP
target_include_directories(SpotifyCPP PUBLIC include)

# Private include: Thirdparty
target_include_directories(SpotifyCPP PUBLIC thirdparty)


target_link_libraries(SpotifyCPP PRIVATE
        CURL::libcurl
        Threads::Threads
)

# --- Optional Examples
if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()