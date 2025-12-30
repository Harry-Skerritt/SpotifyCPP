# Client

The `Client` class is the main entry point for working within the Spotify Web API

Once the authentication is complete, the Client instance will provide access to all Spotify API endpoints!

## Overview

```c++
// Creating a Client instance
Auth auth({client_key, client_secret});
auth.exchangeCode(code);

Client client(auth);
```
- Holds a reference to an authenticated [`Auth`]() instance
- Manages access tokens internally
- Provides API endpoint wrappers in a similar format to Spotify's own

## Responsibilities
The Client class **is** responsible for:
- Supplying valid access tokens to API calls 
- Automatically refreshing expired tokens when required

It does **not**:
- Perform authentication itself 
- Store client secrets 
- Persist tokens to disk


## Access Token
```c++
std::string token = client.getAccessToken();
```
- Automatically refreshes an expired token
- Each API endpoint handles this internally
- Can be called manually if needed


## Endpoint Accessors
Each method returns an API wrapper responsible for a specific group of Spotify endpoints.

**Available APIs**

| Method       | API                         | Documentation                                        |
|--------------|-----------------------------|------------------------------------------------------|
| album()      | Album endpoints             | [Album Docs](/docs/APIReference/AlbumAPI.md)         |
| artist()     | Artist endpoints            | [Artist Docs](/docs/APIReference/ArtistAPI.md)       |
| audiobook()  | Audiobook endpoints         | [Audiobook Docs](/docs/APIReference/AudiobookAPI.md) |
| browse()     | Search and Market endpoints | [Browse Docs](/docs/APIReference/BrowseAPI.md)       |
| category()   | Category Endpoints          | [Category Docs](/docs/APIReference/CategoryAPI.md)   |
| chapter()    | Chapter Endpoints           | [Chapter Docs](/docs/APIReference/ChapterAPI.md)     |
| episode()    | Episode Endpoints           | [Episode Docs](/docs/APIReference/EpisodeAPI.md)     |
| player()     | Player Endpoints            | [Player Docs](/docs/APIReference/PlayerAPI.md)       |
| playlist()   | Playlist Endpoints          | [Playlist Docs](/docs/APIReference/PlaylistAPI.md)   |
| shows()      | Show Endpoints              | [Show Docs](/docs/APIReference/ShowAPI.md)           |
| track()      | Track Endpoints             | [Track Docs](/docs/APIReference/TrackAPI.md)         |
| users()      | Users Endpoints             | [User Docs](/docs/APIReference/UserAPI.md)           |

### Example
```c++
Client client(auth);

// Fetch an album
auto album = client.album().getAlbum("1U3qu4gDfohAqFrmpLT11l");

// Get playback state
auto playback = client.player().getPlaybackState();

// Access token (optional)
auto token = client.getAccessToken();
```

## Errors
Methods accessed through Client may throw:
- [`APIException`](/docs/Exceptions.md#spotifyapiexception) — Spotify API error
- [`NetworkException`](/docs/Exceptions.md#spotifynetworkexception) — Network failure
- [`LogicException`](/docs/Exceptions.md#spotifylogicexception) — Invalid library state

These exceptions originate from the underlying endpoint APIs.


## See Also:
- [Authentication](/docs/Authentication.md)
- [Album API](/docs/APIReference/AlbumAPI.md)
- [Player API](/docs/APIReference/PlayerAPI.md)
- [Exceptions](/docs/Exceptions.md)