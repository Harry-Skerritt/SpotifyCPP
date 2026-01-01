# Authorisation Types

This page lists all object and data types available for the Spotify Authorisation Flow in the C++ library.  
All types are defined under the `Spotify` namespace.

---

## `ClientCredentials`

Used to store your Spotify Client ID and Secret for authentication

| Field           | Type            | Description                            |
|-----------------|-----------------|----------------------------------------|
| `client_id`     | `std::string`   | Your Spotify application Client ID     |
| `client_secret` | `std::string`   | Your Spotify application Client Secret |

---

## `AuthResponse`

Represents the response from Spotify when exchanging an authorization code or refreshing a token

| Field            | Type                                                 | Description                                                   |
|------------------|------------------------------------------------------|---------------------------------------------------------------|
| `access_token`   | `std::string`                                        | The token used to authenticate requests to the Spotify API    |
| `token_type`     | `std::string`                                        | The type of token (typically `"Bearer"`)                      |
| `scope`          | `std::string`                                        | The scopes granted to the token, space-separated              |
| `expire_time`    | `std::chrono::time_point<std::chrono::system_clock>` | The exact time when the token will expire                     |
| `refresh_token`  | `std::string`                                        | Token used to refresh the access token without re-authorising |
| `response_code`  | `HTTPStatus_Code`                                    | HTTP status code returned from Spotify API                    |

---

### Notes

- `ClientCredentials` are typically loaded from environment variables or a `.env` file
- `AuthResponse` is returned by methods like `Auth::exchangeCode()` or `Auth::refreshToken()`
- Always check `expire_time` before making requests; refresh the token if needed - this is done automatically within most API endpoints  

### See Also

- [Authentication](/docs/Tutorials/Authentication.md)
- [Tools](/docs/Utilities/Tools.md)