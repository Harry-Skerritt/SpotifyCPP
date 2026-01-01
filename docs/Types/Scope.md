# Scope

This page lists all Spotify OAuth scopes supported by the library.

In C++, each scope is available as a typed constant under `Scope::`, e.g., `Scope::ReadState`.

> **Note:** The underlying string for each scope is still Spotify’s case-sensitive value.

*See Also: [Spotify Scope](thttps://developer.spotify.com/documentation/web-api/concepts/scopes) for more information about scopes - including which endpoints need which scopes*


| Library Scope                      | Spotify Scope               | Description                                                                                                                                |
|------------------------------------|-----------------------------|--------------------------------------------------------------------------------------------------------------------------------------------|
| `Scope::UGCImageUpload`            | ugc-image-upload            | Write access to user-provided images                                                                                                       |
| `Scope::UserReadPlaybackState`     | user-read-playback-state    | Read access to a user’s player state                                                                                                       |
| `Scope::UserModifyPlaybackState`   | user-modify-playback-state  | Write access to a user’s playback state                                                                                                    |
| `Scope::UserReadCurrentlyPlaying`  | user-read-currently-playing | Read access to a user’s currently playing content                                                                                          |
| `Scope::AppRemoteControl`          | app-remote-control          | Remote control playback of Spotify. This scope is currently available to Spotify iOS and Android SDKs                                      |
| `Scope::Streaming`                 | streaming                   | Control playback of a Spotify track. This scope is currently available to the Web Playback SDK. The user must have a Spotify Premium account |
| `Scope::PlaylistReadPrivate`       | playlist-read-private       | Read access to user's private playlists                                                                                                    |
| `Scope::PlaylistReadCollaborative` | playlist-read-collaborative | Include collaborative playlists when requesting a user's playlists                                                                         |
| `Scope::PlaylistModifyPrivate`     | playlist-modify-private     | Write access to a user's private playlists                                                                                                 |
| `Scope::PlaylistModifyPublic`      | playlist-modify-public      | Write access to a user's public playlists                                                                                                  |
| `Scope::UserFollowModify`          | user-follow-modify          | Write/delete access to the list of artists and other users that the user follows                                                           |
| `Scope::UserFollowRead`            | user-follow-read            | Read access to the list of artists and other users that the user follows                                                                   |
| `Scope::UserReadPlaybackPosition`  | user-read-playback-position | Read access to a user’s playback position in a content                                                                                     |
| `Scope::UserTopRead`               | user-top-read               | Read access to a user's top artists and tracks                                                                                             |
| `Scope::UserReadRecentlyPlayed`    | user-read-recently-played   | Read access to a user’s recently played tracks                                                                                             |
| `Scope::UserLibraryModify`         | user-library-modify         | Write/delete access to a user's "Your Music" library                                                                                       |
| `Scope::UserLibraryRead`           | user-library-read           | Read access to a user's library                                                                                                            |
| `Scope::UserReadEmail`             | user-read-email             | Read access to user’s email address                                                                                                        |
| `Scope::UserReadPrivate`           | user-read-private           | Read access to user’s subscription details (type of user account)                                                                          |
| `Scope::UserPersonalized`          | user-personalized           | Get personalized content for the user                                                                                                      |
| `Scope::UserSOALink`               | user-soa-link               | Link a partner user account to a Spotify user account                                                                                      |
| `Scope::UserSOAUnlink`             | user-soa-unlink             | Unlink a partner user account from a Spotify account                                                                                       |
| `Scope::SOAManageEntitlements`     | soa-manage-entitlements     | Modify entitlements for linked users                                                                                                       |
| `Scope::SOAManagePartner`          | soa-manage-partner          | Update partner information                                                                                                                 |
| `Scope::SOACreatePartner`          | soa-create-partner          | Create new partners, platform partners only                                                                                                |

## See Also
- [Authentication](/docs/Authentication.md)