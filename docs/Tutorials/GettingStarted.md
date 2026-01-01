# Getting Started

## Step 1 - Creating a Spotify Developer App

To use this library you need, a Spotify developer account, along with an active Spotify developer app

- Go to [Spotify Developer Dashboard](https://developer.spotify.com/dashboard)
- Create a new app and obtain a **Client ID** and **Client Secret**
- Set the redirect URI (e.g. `http://127.0.0.1:8888/callback`)

## Step 2 - Load Credentials

## Step 2 – Load Credentials

There are several ways to supply your Spotify credentials.

This library provides a helper for loading them from a `.env` file.

### Example `.env` file

```env
SPOTIFY_CLIENT_KEY=your_client_id_here
SPOTIFY_CLIENT_SECRET=your_client_secret_here
```

### Loading credentials in code
```c++
#include <spotify/spotify.hpp>
#include <Tools.hpp>

Tools::loadEnv("/path/to/.env");

const char* client_key = std::getenv("SPOTIFY_CLIENT_KEY");
const char* client_secret = std::getenv("SPOTIFY_CLIENT_SECRET");

Spotify::Auth auth({client_key, client_secret});
```
⚠️ Never commit your `.env` file or credentials to source control.

## Step 3 - Authorisation
Once your credentials are loaded, you can authorize your application.

Follow the full authorization flow documentation here: [Authentication](/docs/Tutorials/Authentication.md)