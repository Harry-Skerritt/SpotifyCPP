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

# --- Helper to put binaries in the right subfolder ---
function(set_example_output_dir TARGET_NAME CATEGORY SUBFOLDER)
    set_target_properties(${TARGET_NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples/${CATEGORY}/${SUBFOLDER}")

    # Handle Multi-config (Debug/Release folders) for macOS/Windows
    if(CMAKE_CONFIGURATION_TYPES)
        foreach(CONFIG ${CMAKE_CONFIGURATION_TYPES})
            string(TOUPPER ${CONFIG} CONFIG_UPPER)
            set_target_properties(${TARGET_NAME} PROPERTIES
                    RUNTIME_OUTPUT_DIRECTORY_${CONFIG_UPPER} "${BASE_DIR}"
            )
        endforeach()
    endif()
endfunction()


# --- Real World Examples
add_executable(example_nowPlaying examples/realworld/now_playing.cpp)
target_link_libraries(example_nowPlaying PRIVATE SpotifyAPILib)
set_example_output_dir(example_nowPlaying "realworld" "now_playing")

# --- Endpoint Examples ---
# --- Auth Examples ---
add_executable(example_authManual examples/endpoints/auth/authManualExample.cpp)
target_link_libraries(example_authManual PRIVATE SpotifyAPILib)
set_example_output_dir(example_authManual "endpoints" "auth")

add_executable(example_authServer examples/endpoints/auth/authServerExample.cpp)
target_link_libraries(example_authServer PRIVATE SpotifyAPILib)
set_example_output_dir(example_authServer "endpoints" "auth")

#Copy the HTML file to the same folder as the binaries
configure_file(
        "examples/endpoints/auth/index.html"
        "${CMAKE_BINARY_DIR}/examples/endpoints/auth/index.html"
        COPYONLY
)


# --- Album Examples ---
add_executable(example_getAlbums examples/endpoints/albums/getAlbumExample.cpp)
target_link_libraries(example_getAlbums PRIVATE SpotifyAPILib)
set_example_output_dir(example_getAlbums "endpoints" "albums")

add_executable(example_getAlbumTracks examples/endpoints/albums/getAlbumTracksExample.cpp)
target_link_libraries(example_getAlbumTracks PRIVATE SpotifyAPILib)
set_example_output_dir(example_getAlbumTracks "endpoints" "albums")

add_executable(example_getUserAlbums examples/endpoints/albums/getUserAlbumsExample.cpp)
target_link_libraries(example_getUserAlbums PRIVATE SpotifyAPILib)
set_example_output_dir(example_getUserAlbums "endpoints" "albums")

add_executable(example_saveUserAlbums examples/endpoints/albums/saveAlbumForUserExample.cpp)
target_link_libraries(example_saveUserAlbums PRIVATE SpotifyAPILib)
set_example_output_dir(example_saveUserAlbums "endpoints" "albums")

add_executable(example_deleteUserAlbums examples/endpoints/albums/removeAlbumForUserExample.cpp)
target_link_libraries(example_deleteUserAlbums PRIVATE SpotifyAPILib)
set_example_output_dir(example_deleteUserAlbums "endpoints" "albums")

add_executable(example_newReleases examples/endpoints/albums/newReleaseExample.cpp)
target_link_libraries(example_newReleases PRIVATE SpotifyAPILib)
set_example_output_dir(example_newReleases "endpoints" "albums")


# --- Artist Examples ---
add_executable(example_getArtists examples/endpoints/artists/getArtistExample.cpp)
target_link_libraries(example_getArtists PRIVATE SpotifyAPILib)
set_example_output_dir(example_getArtists "endpoints" "artists")

add_executable(example_getArtistsAlbums examples/endpoints/artists/getArtistsAlbumsExample.cpp)
target_link_libraries(example_getArtistsAlbums PRIVATE SpotifyAPILib)
set_example_output_dir(example_getArtistsAlbums "endpoints" "artists")

add_executable(example_getArtistTopTracks examples/endpoints/artists/getArtistTopTracksExample.cpp)
target_link_libraries(example_getArtistTopTracks PRIVATE SpotifyAPILib)
set_example_output_dir(example_getArtistTopTracks "endpoints" "artists")


# --- Audiobook Examples ---
add_executable(example_getAudiobook examples/endpoints/audiobooks/getAudiobookExample.cpp)
target_link_libraries(example_getAudiobook PRIVATE SpotifyAPILib)
set_example_output_dir(example_getAudiobook "endpoints" "audiobooks")

add_executable(example_getAudiobookChapters examples/endpoints/audiobooks/getAudiobookChapters.cpp)
target_link_libraries(example_getAudiobookChapters PRIVATE SpotifyAPILib)
set_example_output_dir(example_getAudiobookChapters "endpoints" "audiobooks")

add_executable(example_getUserAudiobooks examples/endpoints/audiobooks/getUserAudiobooksExample.cpp)
target_link_libraries(example_getUserAudiobooks PRIVATE SpotifyAPILib)
set_example_output_dir(example_getUserAudiobooks "endpoints" "audiobooks")

add_executable(example_saveUserAudiobook examples/endpoints/audiobooks/saveAudiobookForUser.cpp)
target_link_libraries(example_saveUserAudiobook PRIVATE SpotifyAPILib)
set_example_output_dir(example_saveUserAudiobook "endpoints" "audiobooks")

add_executable(example_deleteUserAudiobook examples/endpoints/audiobooks/removeAudiobookForUser.cpp)
target_link_libraries(example_deleteUserAudiobook PRIVATE SpotifyAPILib)
set_example_output_dir(example_deleteUserAudiobook "endpoints" "audiobooks")


# --- Browse Examples ---
add_executable(example_getAvailableMarkets examples/endpoints/browse/getAvailableMarketsExample.cpp)
target_link_libraries(example_getAvailableMarkets PRIVATE SpotifyAPILib)
set_example_output_dir(example_getAvailableMarkets "endpoints" "browse")

add_executable(example_Search examples/endpoints/browse/searchExample.cpp)
target_link_libraries(example_Search PRIVATE SpotifyAPILib)
set_example_output_dir(example_Search "endpoints" "browse")



# --- Category Examples ---
add_executable(example_getSingleCategory examples/endpoints/categories/getSingleCategoryExample.cpp)
target_link_libraries(example_getSingleCategory PRIVATE SpotifyAPILib)
set_example_output_dir(example_getSingleCategory "endpoints" "categories")

add_executable(example_getMultiCategory examples/endpoints/categories/getMultipleCategoriesExample.cpp)
target_link_libraries(example_getMultiCategory PRIVATE SpotifyAPILib)
set_example_output_dir(example_getMultiCategory "endpoints" "categories")


# --- Chapter Examples ---
add_executable(example_getSingleChapter examples/endpoints/chapters/getSingleChapterExample.cpp)
target_link_libraries(example_getSingleChapter PRIVATE SpotifyAPILib)
set_example_output_dir(example_getSingleChapter "endpoints" "chapters")

add_executable(example_getMultiChapter examples/endpoints/chapters/getMultipleChaptersExample.cpp)
target_link_libraries(example_getMultiChapter PRIVATE SpotifyAPILib)
set_example_output_dir(example_getMultiChapter "endpoints" "chapters")


# --- Episode Examples ---
add_executable(example_getEpisodes examples/endpoints/episodes/getEpisodeExample.cpp)
target_link_libraries(example_getEpisodes PRIVATE SpotifyAPILib)
set_example_output_dir(example_getEpisodes "endpoints" "episodes")

add_executable(example_getUsersEpisodes examples/endpoints/episodes/getUserEpisodesExample.cpp)
target_link_libraries(example_getUsersEpisodes PRIVATE SpotifyAPILib)
set_example_output_dir(example_getUsersEpisodes "endpoints" "episodes")

add_executable(example_saveUserEpisode examples/endpoints/episodes/saveEpisodeForUserExample.cpp)
target_link_libraries(example_saveUserEpisode PRIVATE SpotifyAPILib)
set_example_output_dir(example_saveUserEpisode "endpoints" "episodes")

add_executable(example_deleteUserEpisode examples/endpoints/episodes/removeEpisodeForUserExample.cpp)
target_link_libraries(example_deleteUserEpisode PRIVATE SpotifyAPILib)
set_example_output_dir(example_deleteUserEpisode "endpoints" "episodes")


# --- Player Examples ---
add_executable(example_getPlaybackState examples/endpoints/player/getPlaybackStateExample.cpp)
target_link_libraries(example_getPlaybackState PRIVATE SpotifyAPILib)
set_example_output_dir(example_getPlaybackState "endpoints" "player")

add_executable(example_transferPlayback examples/endpoints/player/transferPlaybackExample.cpp)
target_link_libraries(example_transferPlayback PRIVATE SpotifyAPILib)
set_example_output_dir(example_transferPlayback "endpoints" "player")

add_executable(example_getDevices examples/endpoints/player/getDevicesExample.cpp)
target_link_libraries(example_getDevices PRIVATE SpotifyAPILib)
set_example_output_dir(example_getDevices "endpoints" "player")

add_executable(example_getCurrentlyPlaying examples/endpoints/player/getCurrentTrackExample.cpp)
target_link_libraries(example_getCurrentlyPlaying PRIVATE SpotifyAPILib)
set_example_output_dir(example_getCurrentlyPlaying "endpoints" "player")

add_executable(example_playPause examples/endpoints/player/playPauseExample.cpp)
target_link_libraries(example_playPause PRIVATE SpotifyAPILib)
set_example_output_dir(example_playPause "endpoints" "player")

# Skip track
# Seek track
# Repeat Mode
# Volume
# Shuffle

add_executable(example_getRecentlyPlayed examples/endpoints/player/getRecentlyPlayedExample.cpp)
target_link_libraries(example_getRecentlyPlayed PRIVATE SpotifyAPILib)
set_example_output_dir(example_getRecentlyPlayed "endpoints" "player")

add_executable(example_getUserQueue examples/endpoints/player/getUserQueueExample.cpp)
target_link_libraries(example_getUserQueue PRIVATE SpotifyAPILib)
set_example_output_dir(example_getUserQueue "endpoints" "player")

add_executable(example_addToQueue examples/endpoints/player/addToQueueExample.cpp)
target_link_libraries(example_addToQueue PRIVATE SpotifyAPILib)
set_example_output_dir(example_addToQueue "endpoints" "player")



# --- Playlist Examples ---
add_executable(example_getPlaylist examples/endpoints/playlists/getPlaylistExample.cpp)
target_link_libraries(example_getPlaylist PRIVATE SpotifyAPILib)
set_example_output_dir(example_getPlaylist "endpoints" "playlist")

add_executable(example_createAndManipulate examples/endpoints/playlists/createAndManipulatePlaylistExample.cpp)
target_link_libraries(example_createAndManipulate PRIVATE SpotifyAPILib)
set_example_output_dir(example_createAndManipulate "endpoints" "playlist")

add_executable(example_getCurrentUsersPlaylist examples/endpoints/playlists/getCurrentUsersPlaylistsExample.cpp)
target_link_libraries(example_getCurrentUsersPlaylist PRIVATE SpotifyAPILib)
set_example_output_dir(example_getCurrentUsersPlaylist "endpoints" "playlist")

add_executable(example_getUsersPlaylist examples/endpoints/playlists/getUsersPlaylistsExample.cpp)
target_link_libraries(example_getUsersPlaylist PRIVATE SpotifyAPILib)
set_example_output_dir(example_getUsersPlaylist "endpoints" "playlist")

add_executable(example_getPlaylistItems examples/endpoints/playlists/getPlaylistItemsExamples.cpp)
target_link_libraries(example_getPlaylistItems PRIVATE SpotifyAPILib)
set_example_output_dir(example_getPlaylistItems "endpoints" "playlist")

add_executable(example_getPlaylistCover examples/endpoints/playlists/getPlaylistCoverExample.cpp)
target_link_libraries(example_getPlaylistCover PRIVATE SpotifyAPILib)
set_example_output_dir(example_getPlaylistCover "endpoints" "playlist")





# --- Track Examples ---
add_executable(example_getTrack examples/endpoints/tracks/getTrackExample.cpp)
target_link_libraries(example_getTrack PRIVATE SpotifyAPILib)
set_example_output_dir(example_getTrack "endpoints" "tracks")

add_executable(example_getUserTracks examples/endpoints/tracks/getUserTracksExample.cpp)
target_link_libraries(example_getUserTracks PRIVATE SpotifyAPILib)
set_example_output_dir(example_getUserTracks "endpoints" "tracks")

add_executable(example_saveUserTracks examples/endpoints/tracks/saveTrackForUserExample.cpp)
target_link_libraries(example_saveUserTracks PRIVATE SpotifyAPILib)
set_example_output_dir(example_saveUserTracks "endpoints" "tracks")

add_executable(example_deleteUserTracks examples/endpoints/tracks/removeTrackForUserExample.cpp)
target_link_libraries(example_deleteUserTracks PRIVATE SpotifyAPILib)
set_example_output_dir(example_deleteUserTracks "endpoints" "tracks")

# --- Users Examples ---
add_executable(example_getCurrentUser examples/endpoints/users/getCurrentUserExample.cpp)
target_link_libraries(example_getCurrentUser PRIVATE SpotifyAPILib)
set_example_output_dir(example_getCurrentUser "endpoints" "users")

add_executable(example_getUsersTopItems examples/endpoints/users/getUsersTopItemsExample.cpp)
target_link_libraries(example_getUsersTopItems PRIVATE SpotifyAPILib)
set_example_output_dir(example_getUsersTopItems "endpoints" "users")

add_executable(example_followUnfollowArtistsAndUsers examples/endpoints/users/followArtistsAndUsersExample.cpp)
target_link_libraries(example_followUnfollowArtistsAndUsers PRIVATE SpotifyAPILib)
set_example_output_dir(example_followUnfollowArtistsAndUsers "endpoints" "users")

add_executable(example_getFollowedArtists examples/endpoints/users/getFollowedArtistExample.cpp)
target_link_libraries(example_getFollowedArtists PRIVATE SpotifyAPILib)
set_example_output_dir(example_getFollowedArtists "endpoints" "users")

