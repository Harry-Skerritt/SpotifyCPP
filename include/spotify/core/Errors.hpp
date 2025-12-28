//
// Created by Harry Skerritt on 28/12/2025.
//

#ifndef ERRORS_HPP
#define ERRORS_HPP

#pragma once

#include <string>
#include <stdexcept>
#include <optional>

#include "nlohmann/json.hpp"
#include "spotify/util/Http.hpp"

// Note: Briefs are AI generated - Replace before deployment

namespace Spotify {

    struct ErrorDetails {
        int status;
        std::string message;
        std::string reason;
    };


    /**
     * @class Exception
     * @brief Base exception for all Spotify library errors.
     */
    class Exception : public std::runtime_error {
    public:
        explicit Exception(const std::string &message) : std::runtime_error(message) {}
    };


    /**
     * @class APIException
     * @brief Thrown when the Spotify API returns a non-success status code (4xx or 5xx).
     */
    class APIException : public Exception {
        ErrorDetails m_details;
    public:
        APIException(const ErrorDetails &details)
        : Exception("Spotify API [" + std::to_string(details.status) + "]: " + details.message),
          m_details(details) {}

        [[nodiscard]] int status() const { return m_details.status; }
        [[nodiscard]] std::string message() const { return m_details.message; }
        [[nodiscard]] std::string reason() const { return m_details.reason; }
    };

    /**
     * @class RateLimitException
     * @brief Specifically thrown on HTTP 429 errors. Includes cooldown timing.
     */

    class RateLimitException : public APIException {
        int m_retry_after_seconds;
    public:
        RateLimitException(const ErrorDetails& details, int retry_after)
            : APIException(details), m_retry_after_seconds(retry_after) {}

        [[nodiscard]] int retryAfter() const { return m_retry_after_seconds; }
    };


    /**
     * @class ParseException
     * @brief Thrown when JSON deserialization fails or the API returns malformed data.
     */
    class ParseException : public Exception {
        std::string m_raw_body;
    public:
        ParseException(const std::string& msg, const std::string& body)
            : Exception("Parse Error: " + msg), m_raw_body(body) {}

        [[nodiscard]] std::string getRawBody() const { return m_raw_body; }
    };


    /**
     * @class LogicException
     * @brief Thrown for programmer errors (e.g., bad arguments or uninitialized state).
     */
    class LogicException : public Exception {
    public:
        using Exception::Exception;
    };


    /**
 * @class NetworkException
 * @brief Thrown when a low-level network failure occurs (e.g., DNS failure,
 * connection timeout, or port binding issues).
 * @sa Exception
 */
    class NetworkException : public Exception {
        int m_libcurl_code;
    public:

        explicit NetworkException(const std::string& msg, int curl_code = 0)
            : Exception("Network Error: " + msg), m_libcurl_code(curl_code) {}

        [[nodiscard]] int libcurlCode() const { return m_libcurl_code; }
    };




    // Todo: Add more



    class ErrorHandler {
    public:
        /**
         * @brief Validates an HTTP result.
         * @param result The result from a curl request.
         * @throws APIException, RateLimitException, or ParseException if the request failed.
         */
        static void verifyResponse(const HTTP::Result& result) {
            int code = static_cast<int>(result.code);

            // Success
            if (code >= 200 && code < 300) return;

            try {
                auto j = nlohmann::json::parse(result.body);

                if (j.is_object() && j.contains("error")) {
                    auto error_obj = j["error"];

                    std::string msg = error_obj.is_string()
                              ? error_obj.get<std::string>()
                              : error_obj.value("message", "Unknown API Error");

                    Spotify::ErrorDetails details {
                        code,
                        msg,
                        j.value("reason", "UNKNOWN_REASON")
                    };

                    if (result.code == RFC2616_Code::TOO_MANY_REQUESTS) {
                        throw Spotify::RateLimitException(details, 30);
                    }
                    throw Spotify::APIException(details);
                }

                throw Spotify::ParseException("Unexpected JSON format: " + j.dump(), result.body);

            } catch (const nlohmann::json::parse_error& e) {
                throw Spotify::ParseException("Non-JSON response: " + result.body, result.body);
            } catch (const nlohmann::json::type_error& e) {
                throw Spotify::ParseException("JSON Type Mismatch: " + std::string(e.what()), result.body);
            }

        }
    };

}

#endif //ERRORS_HPP
