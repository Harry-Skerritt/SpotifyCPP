# Exceptions
This document describes all exceptions that may be thrown by the Spotify C++ API library, when they occur, and how they should be handled.

| Category | Exception |
|--------|-----------|
| API | APIException, RateLimitException |
| Network | NetworkException |
| Parsing | ParseException |
| Logic | LogicException |
| Validation | InvalidIDException, InvalidResourceException |

The library uses exceptions to signal:
- Spotify Web API errors
- Network and transport failures
- JSON parsing issues
- Invalid input or misuse of the library

### Exception Hierarchy
```text
std::exception
 ├── std::runtime_error
 │    └── Spotify::Exception
 │         ├── Spotify::APIException
 │         │    └── Spotify::RateLimitException
 │         ├── Spotify::ParseException
 │         ├── Spotify::LogicException
 │         └── Spotify::NetworkException
 └── std::invalid_argument
      ├── Spotify::InvalidIDException
      └── Spotify::InvalidResourceException
```

## Base Exception 

### `Spotify::Exception`

The base class for all library specific runtime errors
- Thrown when the library encounters an unrecoverable runtime error
- Can be used to catch **all library** exceptions at once
- Inherits from `std::runtime_error`

**Example**

```c++
catch (const Spotify::Exception& e) {
    std::cerr << e.what() << std::endl;
}
```

## API Errors

### `Spotify::APIException`
Thrown when the Spotify Web API returns a non-success HTTP status code (4xx or 5xx).

**Common Causes:**
- Invalid or expired access token
- Missing required scopes
- Invalid request parameters
- Resource not found
- Server-side errors

**Example**

```c++
catch (const Spotify::APIException& e) {
    std::cerr << "Status: " << e.status() << std::endl;
    std::cerr << "Message: " << e.message() << std::endl;
}
```

Most APIExceptions are recoverable by adjusting input, scopes, or authentication.

### `Spotify::RateLimitException`

Specialized exception thrown when the Spotify API responds with HTTP 429 (Too Many Requests).
- Inherits from Spotify::APIException
- Indicates the client has exceeded Spotify’s rate limits

**Additional Information**

```c++
int retryAfter() const; // Cooldown time in seconds
```
Clients should delay further requests until the retry period has elapsed.

**Example**
```c++
catch (const Spotify::RateLimitException& e) {
    std::cout << "Rate limited. Retry after "
              << e.retryAfter() << " seconds." << std::endl;
}
```


## Parsing Errors

### `Spotify::ParseException`
Thrown when the library fails to parse a response from the Spotify API.

This can occur when:
- Spotify returns malformed JSON 
- The response body does not match the expected schema 
- A non-JSON response is returned unexpectedly

**Additional Information**
```c++
std::string getRawBody() const;
```
This allows inspection of the raw response body for debugging.

**Example**
```c++
catch (const Spotify::ParseException& e) {
    std::cerr << e.what() << std::endl;
    std::cerr << "Raw Body: " << e.getRawBody() << std::endl;
}
```

## Network Errors

### `Spotify::NetworkException`

Thrown when a low-level network failure occurs.

Examples include:
- DNS resolution failure
- Connection timeout
- TLS or socket errors
- Local port binding failures
- libcurl transport errors

**Additional Information**
```c++
int libcurlCode() const;
```
The libcurl error code may be used for deeper diagnostics.


## Logic Errors

### `Spotify::LogicException`

Thrown when the library is used incorrectly or enters an invalid state.

Examples:
- Attempting to use the Client before authentication
- Missing required configuration
- Invalid arguments passed to internal logic

This exception usually indicates a programming error, not a runtime failure.

## Input & Validation Errors

### `Spotify::InvalidIDException`

Thrown when a Spotify ID does not match the expected format.

Rules:
- Exactly 22 characters
- Alphanumeric (Base62)

Inherits from `std::invalid_argument`.

### `Spotify::InvalidResourceException`

Thrown when a Spotify URL or URI does not contain a valid or supported resource type.

Examples:
- Unsupported resource paths 
- Malformed Spotify URLs

Inherits from `std::invalid_argument`.


## Error Handling Internals

### `Spotify::ErrorHandler`

Internal utility used by the library to validate HTTP responses.
- Inspects HTTP status codes
- Parses error responses from Spotify
- Throws:
  - APIException 
  - RateLimitException 
  - ParseException

*This class is not typically used directly by library consumers.*


## Non-Throwing Alternatives
Some parsing utilities provide `try*` variants that do not throw exceptions.

**Example**
```c++
std::string error;
auto id = Spotify::Parse::tryExtractID(input, &error);

if (!id) {
    std::cerr << "Failed to parse ID: " << error << std::endl;
}
```
These return `std::optional` and optionally populate an error message.

## Recommended Catch Strategy
```c++
try {
    // Spotify API calls
}
catch (const Spotify::RateLimitException& e) {
    // Handle rate limiting
}
catch (const Spotify::APIException& e) {
    // Spotify API error
}
catch (const Spotify::NetworkException& e) {
    // Network failure
}
catch (const Spotify::Exception& e) {
    // Any other library error
}
catch (const std::exception& e) {
    // Standard C++ error
}
```

## See Also
- [Authentication](/docs/Authentication.md)
- [Client](/docs/APIReference/Client.md)
- [Parsing Utilities](/docs/utilities/Parsing.md)