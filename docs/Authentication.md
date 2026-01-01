# Authentication

## Authorisation Code Flow
*Note: [Authorisation Code Flow](https://developer.spotify.com/documentation/web-api/tutorials/code-flow) is the only flow implemented within the library at the moment*

The steps below outline how to use OAuth2 to obtain a Spotify authorisation token

## Step 1 - Generate an Authorisation URL
The library provides an easy way to generate an authorisation URL

An example of generating an authorization URL is shown below

```c++
// Step 1: Generate the authorization URL
auto url = auth.createAuthoriseURL(
    "http://127.0.0.1:8888/callback",
    {
        Spotify::Scope::UserReadPlaybackState, 
        Spotify::Scope::UserReadCurrentlyPlaying
    });
```

**⚠️ The redirect URI must match exactly what is registered in your Spotify developer app, including trailing slashes**

See information on [`Scopes`](/docs/APIReference/Scopes.md)

## Step 2 - Capture the code
Once you have the authorisation URL the user will need to click it and allow the app access

This will then send them to the configured redirect uri with a code as part of its URL -
This can either be captured manually in a way you choose, but the library does provide easy ways of doing this

The `AuthServer` can make capturing the code easy:

*(The `AuthServer` starts a temporary local HTTP server to receive the redirect
from Spotify and extract the authorization code automatically)*


```c++
// Step 2: Capture the access code
Spotify::AuthServer::openBrowser(url);
std::string code = Spotify::AuthServer::waitForCode("127.0.0.1", 8888);
```

The `waitForCode` function will return the code

*See more on [`AuthServer`](/docs/AuthServer.md)*

## Step 3 - Exchange the Code

The authorization code is not yet an access token, however the one line of code below can exchange the code for the token

```c++
// Step 3: Exchange code for token
auth.exchangeCode(code);
```

*See more on [`AuthResponse`](/docs/Types/Scope.md)*


## Step 4 - Refreshing Access Token

The access token is only valid for 3600 seconds (1 hour)

After this time it needs refreshing

The `.getAccessToken()` method within the `Client` handles this refresh automatically so most applications do not need to call `refreshAccessToken()` directly,
but it can be done manually as explained below

```c++
// Step 4: Refresh access token once expired
auth.refreshAccessToken();
```

*See more on [`Client`](/docs/APIReference/Client.md)*

# Full Flow Example


A complete, minimal authentication example can be found here:

**[`examples/realworld/authenticate.cpp`](/examples/realworld/authenticate.cpp)**

```c++
#include <spotify/spotify.hpp>

using namespace Spotify;

int main() {
    std::string env_path = "/Volumes/Data/Code/C++/2025/SpotifyAPILib/.env";
    Tools::loadEnv(env_path);

    const char* client_key = std::getenv("SPOTIFY_CLIENT_KEY");
    const char* client_secret = std::getenv("SPOTIFY_CLIENT_SECRET");

    if (!client_key || !client_secret) {
        throw std::runtime_error("SPOTIFY_CLIENT_KEY or SECRET not found in environment.");
    }

    try {
        Auth auth({client_key, client_secret});

        auto url = auth.createAuthoriseURL(
            "http://127.0.0.1:8888/callback",
            { Scope::UserReadPlaybackState }
        );

        AuthServer::openBrowser(url);
        std::string code = AuthServer::waitForCode("127.0.0.1", 8888);

        auth.exchangeCode(code);
        
        // Fully authenticated client, ready to make API calls
        Client client(auth);
    }
    catch (const Exception& e) {
        std::cerr << "Authentication failed: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
```



### Notes
- Keep your Client ID and Secret private. **Do not** commit them publicly
- Tokens expire - refresh them for long-running applications
- Scopes must match the endpoints you intend to call

## *See Next: [Client](/docs/APIReference/Client.md)*