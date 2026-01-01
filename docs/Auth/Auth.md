# Auth

The `Spotify::Auth` class is the central manager for handling the **Authorization Code Flow**. It manages client credentials, builds the initial authorization URL, exchanges authorization codes for access tokens, and handles automatic token refreshing.

All logic for managing the session's lifecycle is contained within the `Spotify::Auth` namespace.

*See: [Authentication](/docs/Tutorials/Authentication.md) for a tutorial*

---

## Table of Contents

- [Overview](#overview)
- [Initialization](#initialization)
- [Authorization Flow](#authorization-flow)
- [Token Management](#token-management)

---

## Overview

The `Auth` class implements the standard OAuth 2.0 flow required by Spotify:
1.  **URL Generation**: Create a link for the user to visit and approve permissions.
2.  **Code Exchange**: Take the code from the redirect and trade it for an `access_token` and `refresh_token`.
3.  **Automatic Refresh**: Check for expiration and use the `refresh_token` to stay logged in without further user interaction.



---

## Initialization

### `Auth(const ClientCredentials& keys)`

To begin, initialize the class with your **Client ID** and **Client Secret** found in the [Spotify Developer Dashboard](https://developer.spotify.com/dashboard).

| Parameter | Type | Description |
| :--- | :--- | :--- |
| `keys` | `const ClientCredentials&` | Struct containing `client_id` and `client_secret`. |

**Throws**
- `Spotify::LogicException` if the provided keys are empty.

---

## Authorization Flow

### `createAuthoriseURL( const std::string& redirect_uri, const std::vector<Scope>& scopes, const std::optional<std::string>& state)`

Generates the URL where the user will log in and grant permissions to your app.

| Parameter        | Type                         | Description                                                                           |
|:-----------------|:-----------------------------|:--------------------------------------------------------------------------------------|
| `redirect_uri`   | `const std::string&`         | The URL Spotify should send the user back to (must match your Dashboard settings).    |
| `scopes`         | `const std::vector<Scope>&`  | List of permissions your app is requesting.                                           |
| `state`          | `std::optional<std::string>` | A security string. If empty, a random 16-character string is generated automatically. |

**Returns**
A `std::string` containing the full authorization URL.

---

### `exchangeCode(const std::string &code)`

Once the user is redirected back to your app with a code, use this function to get the first set of tokens.

| Parameter | Type | Description |
| :--- | :--- | :--- |
| `code` | `const std::string&` | The code captured from the redirect URL. |

**Process**
1. Encodes credentials into a Base64 Basic Auth header.
2. Sends a `POST` request to the `/api/token` endpoint.
3. Parses the JSON response into an `AuthResponse` and stores the `refresh_token`.

---

## Token Management

### `getAccessToken()`

The main way to retrieve the current token for API calls.

**Automatic Refreshing**
If the current token is expired (usually after 1 hour), this function automatically calls `refreshAccessToken()` before returning a fresh token.

**Returns**
A `std::string` containing a valid access token.

---

### `refreshAccessToken(const std::optional<std::string>& refresh_token)`

Manually triggers a token refresh using the stored `refresh_token`.

| Parameter | Type | Description |
| :--- | :--- | :--- |
| `refresh_token` | `std::optional<std::string>` | Optional override for the token to use. Defaults to the internal stored token. |

---

## Notes

- **Basic Auth**: This class automatically handles the `Authorization: Basic <base64>` header required by Spotify's token endpoint.
- **Expiration Tracking**: The library tracks `expire_time` by taking the current system time and adding the `expires_in` seconds returned by Spotify.
- **Security**: Always provide a `state` or let the library generate one to prevent CSRF attacks.
