cmake_minimum_required(VERSION 3.20)
project(SpotifyAPILib VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)



# --- Library ---
add_library(SpotifyAPILib STATIC
        src/auth/Auth.cpp
        src/auth/AuthServer.cpp
        src/core/Client.cpp
        src/util/Http.cpp
        src/util/Tools.cpp
        src/util/JsonMapping.cpp
        src/api/BaseAPI.cpp
        src/api/AlbumAPI.cpp
        src/api/ArtistAPI.cpp
        src/api/AudiobookAPI.cpp
        src/api/BrowseAPI.cpp
        src/api/CategoryAPI.cpp
        src/api/ChapterAPI.cpp
        src/api/EpisodeAPI.cpp
        src/api/PlayerAPI.cpp


)

# Public includes: SpotifyAPILib
target_include_directories(SpotifyAPILib PUBLIC include)

# Private include: Thirdparty
target_include_directories(SpotifyAPILib PUBLIC thirdparty)

# --- Dependencies ---
find_package(CURL REQUIRED)
find_package(Threads REQUIRED)

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


# --- Album Examples ---
add_executable(example_getAlbums examples/albums/getAlbumExample.cpp)
target_link_libraries(example_getAlbums PRIVATE SpotifyAPILib)
set_example_output_dir(example_getAlbums "albums")

add_executable(example_getAlbumTracks examples/albums/getAlbumTracksExample.cpp)
target_link_libraries(example_getAlbumTracks PRIVATE SpotifyAPILib)
set_example_output_dir(example_getAlbumTracks "albums")

add_executable(example_getUserAlbums examples/albums/getUserAlbumsExample.cpp)
target_link_libraries(example_getUserAlbums PRIVATE SpotifyAPILib)
set_example_output_dir(example_getUserAlbums "albums")

add_executable(example_saveUserAlbums examples/albums/saveAlbumForUserExample.cpp)
target_link_libraries(example_saveUserAlbums PRIVATE SpotifyAPILib)
set_example_output_dir(example_saveUserAlbums "albums")

add_executable(example_deleteUserAlbums examples/albums/removeAlbumForUserExample.cpp)
target_link_libraries(example_deleteUserAlbums PRIVATE SpotifyAPILib)
set_example_output_dir(example_deleteUserAlbums "albums")

add_executable(example_newReleases examples/albums/newReleaseExample.cpp)
target_link_libraries(example_newReleases PRIVATE SpotifyAPILib)
set_example_output_dir(example_newReleases "albums")


# --- Artist Examples ---
add_executable(example_getArtists examples/artists/getArtistExample.cpp)
target_link_libraries(example_getArtists PRIVATE SpotifyAPILib)
set_example_output_dir(example_getArtists "artists")

add_executable(example_getArtistsAlbums examples/artists/getArtistsAlbumsExample.cpp)
target_link_libraries(example_getArtistsAlbums PRIVATE SpotifyAPILib)
set_example_output_dir(example_getArtistsAlbums "artists")

add_executable(example_getArtistTopTracks examples/artists/getArtistTopTracksExample.cpp)
target_link_libraries(example_getArtistTopTracks PRIVATE SpotifyAPILib)
set_example_output_dir(example_getArtistTopTracks "artists")


# --- Audiobook Examples ---
add_executable(example_getAudiobook examples/audiobooks/getAudiobookExample.cpp)
target_link_libraries(example_getAudiobook PRIVATE SpotifyAPILib)
set_example_output_dir(example_getAudiobook "audiobooks")

add_executable(example_getAudiobookChapters examples/audiobooks/getAudiobookChapters.cpp)
target_link_libraries(example_getAudiobookChapters PRIVATE SpotifyAPILib)
set_example_output_dir(example_getAudiobookChapters "audiobooks")

add_executable(example_getUserAudiobooks examples/audiobooks/getUserAudiobooksExample.cpp)
target_link_libraries(example_getUserAudiobooks PRIVATE SpotifyAPILib)
set_example_output_dir(example_getUserAudiobooks "audiobooks")

add_executable(example_saveUserAudiobook examples/audiobooks/saveAudiobookForUser.cpp)
target_link_libraries(example_saveUserAudiobook PRIVATE SpotifyAPILib)
set_example_output_dir(example_saveUserAudiobook "audiobooks")

add_executable(example_deleteUserAudiobook examples/audiobooks/removeAudiobookForUser.cpp)
target_link_libraries(example_deleteUserAudiobook PRIVATE SpotifyAPILib)
set_example_output_dir(example_deleteUserAudiobook "audiobooks")


# --- Browse Examples ---
add_executable(example_getAvailableMarkets examples/browse/getAvailableMarketsExample.cpp)
target_link_libraries(example_getAvailableMarkets PRIVATE SpotifyAPILib)
set_example_output_dir(example_getAvailableMarkets "browse")

add_executable(example_Search examples/browse/searchExample.cpp)
target_link_libraries(example_Search PRIVATE SpotifyAPILib)
set_example_output_dir(example_Search "browse")



# --- Category Examples ---
add_executable(example_getSingleCategory examples/categories/getSingleCategoryExample.cpp)
target_link_libraries(example_getSingleCategory PRIVATE SpotifyAPILib)
set_example_output_dir(example_getSingleCategory "categories")

add_executable(example_getMultiCategory examples/categories/getMultipleCategoriesExample.cpp)
target_link_libraries(example_getMultiCategory PRIVATE SpotifyAPILib)
set_example_output_dir(example_getMultiCategory "categories")


# --- Chapter Examples ---
add_executable(example_getSingleChapter examples/chapters/getSingleChapterExample.cpp)
target_link_libraries(example_getSingleChapter PRIVATE SpotifyAPILib)
set_example_output_dir(example_getSingleChapter "chapters")

add_executable(example_getMultiChapter examples/chapters/getMultipleChaptersExample.cpp)
target_link_libraries(example_getMultiChapter PRIVATE SpotifyAPILib)
set_example_output_dir(example_getMultiChapter "chapters")


# --- Episode Examples ---
add_executable(example_getEpisodes examples/episodes/getEpisodeExample.cpp)
target_link_libraries(example_getEpisodes PRIVATE SpotifyAPILib)
set_example_output_dir(example_getEpisodes "episodes")

add_executable(example_getUsersEpisodes examples/episodes/getUserEpisodesExample.cpp)
target_link_libraries(example_getUsersEpisodes PRIVATE SpotifyAPILib)
set_example_output_dir(example_getUsersEpisodes "episodes")

add_executable(example_saveUserEpisode examples/episodes/saveEpisodeForUserExample.cpp)
target_link_libraries(example_saveUserEpisode PRIVATE SpotifyAPILib)
set_example_output_dir(example_saveUserEpisode "episodes")

add_executable(example_deleteUserEpisode examples/episodes/removeEpisodeForUserExample.cpp)
target_link_libraries(example_deleteUserEpisode PRIVATE SpotifyAPILib)
set_example_output_dir(example_deleteUserEpisode "episodes")


# --- ... ---


# --- Player Examples ---
add_executable(example_getPlaybackState examples/player/getPlaybackStateExample.cpp)
target_link_libraries(example_getPlaybackState PRIVATE SpotifyAPILib)
set_example_output_dir(example_getPlaybackState "player")

add_executable(example_transferPlayback examples/player/transferPlaybackExample.cpp)
target_link_libraries(example_transferPlayback PRIVATE SpotifyAPILib)
set_example_output_dir(example_transferPlayback "player")

add_executable(example_getDevices examples/player/getDevicesExample.cpp)
target_link_libraries(example_getDevices PRIVATE SpotifyAPILib)
set_example_output_dir(example_getDevices "player")

add_executable(example_getCurrentlyPlaying examples/player/getCurrentTrackExample.cpp)
target_link_libraries(example_getCurrentlyPlaying PRIVATE SpotifyAPILib)
set_example_output_dir(example_getCurrentlyPlaying "player")

add_executable(example_playPause examples/player/playPauseExample.cpp)
target_link_libraries(example_playPause PRIVATE SpotifyAPILib)
set_example_output_dir(example_playPause "player")

# Skip track
# Seek track
# Repeat Mode
# Volume
# Shuffle

add_executable(example_getRecentlyPlayed examples/player/getRecentlyPlayedExample.cpp)
target_link_libraries(example_getRecentlyPlayed PRIVATE SpotifyAPILib)
set_example_output_dir(example_getRecentlyPlayed "player")

add_executable(example_getUserQueue examples/player/getUserQueueExample.cpp)
target_link_libraries(example_getUserQueue PRIVATE SpotifyAPILib)
set_example_output_dir(example_getUserQueue "player")

add_executable(example_addToQueue examples/player/addToQueueExample.cpp)
target_link_libraries(example_addToQueue PRIVATE SpotifyAPILib)
set_example_output_dir(example_addToQueue "player")

