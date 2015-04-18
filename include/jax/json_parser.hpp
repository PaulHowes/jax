/**
 * @file json_parser.hpp
 * @brief Hand-coded, general-puropse JSON parser.
 */

#pragma once

#include <regex>
#include <string>

/**
 * @namespace jax
 */
namespace jax {
  /**
   * @brief A simple JSON parser.
   */
  class json_parser {
    public:
      /**
       * @brief Initializes a new jax::json_parser with the JSON text to parse.
       * @param[in] json JSON text to parse.
       */
      json_parser(std::string const& json) : json_(json) {
      }

      /**
       * @brief Parses the input string.
       */
      bool parse() {
        pos = 0;
        return is_value();
      }

    protected:
      /**
       * @brief Used to determine whether the next token is a valid Javascript value.
       * @returns @c true if the next token is a valid Javascript value; otherwise @c false.
       */
      bool is_value() {
        return is_true()   ||
               is_false()  ||
               is_null()   ||
               is_number() ||
               is_string() ||
               is_array()  ||
               is_object();
      }

      /**
       * @brief Used to determine whether the next token is an object.
       * @returns @c true if the next token is an object; otherwise @c false.
       */
      bool is_object() {
        // Punt if the first character isn't a left curly-brace.
        if(!is_match("{")) {
          return false;
        }

        ignore_whitespace();

        // If the next token is a right curly-brace then this is an empty object.
        if(is_match("}")) {
          return true;
        }

        // The next three tokens must be string + ":" + value.
        if(!(is_string() &&
             ignore_whitespace() &&
             is_match(":") &&
             ignore_whitespace() &&
             is_value())) {
          return false;
        }

        ignore_whitespace();

        // If the next token is a comma, then continue to parse comma-separated value tokens.
        while(is_match(",")) {
          ignore_whitespace();

          if(!(is_string() &&
               ignore_whitespace() &&
               is_match(":") &&
               ignore_whitespace() &&
               is_value())) {
            return false;
          }

          ignore_whitespace();
        }

        // The final token must be a right curly-brace.
        if(is_match("}")) {
          return true;
        }

        return false;
      }

      /**
       * @brief Used to determine whether the next token is an array of values.
       * @returns @c true if the next token is an array; otherwise @c false.
       */
      bool is_array() {
        // Punt if the first character isn't a left square-brace.
        if(!is_match("[")) {
          return false;
        }

        ignore_whitespace();

        // If the next token is a right square-brace then this is an empty array.
        if(is_match("]")) {
          return true;
        }

        // The next token must be a value.
        if(!is_value()) {
          return false;
        }

        ignore_whitespace();

        // If the next token is a comma, then continue to parse comma-separated value tokens.
        while(is_match(",")) {
          ignore_whitespace();

          if(!is_value()) {
            return false;
          }

          ignore_whitespace();
        }

        // The final token must be a right square-brace.
        if(is_match("]")) {
          return true;
        }

        return false;
      }

      /**
       * @brief Used to determine whether the next token is "false".
       * @returns @c true if the next token is "false"; otherwise @c false.
       */
      bool is_false() {
        return is_match("false");
      }

      /**
       * @brief Used to determine whether the next token is "null".
       * @returns @c true if the next token is "null"; otherwise @c false.
       */
      bool is_null() {
        return is_match("null");
      }

      /**
       * @brief Used to determine whether the next token is a number.
       * @returns @c true if the next token is a number; otherwise @c false.
       */
      bool is_number() {
        return is_regex_match("[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)?");
      }

      /**
       * @brief Used to determine whether the next token is a string.
       * @returns @c true if the next token is a string; otherwise @c false.
       */
      bool is_string() {
        return is_regex_match("\".*\"");
      }

      /**
       * @brief Used to determine whether the next token is "true".
       * @returns @c true if the next token is "true"; otherwise @c false.
       */
      bool is_true() {
        return is_match("true");
      }

      /**
       * @brief Utility function used to compare strings.
       * @param[in] str String to find at the current parse point.
       * @returns @c true if the token matches; otherwise @c false.
       */
      bool is_match(std::string const& str) {
        size_t len = str.length();
        if(json_.substr(pos, len).compare(str) == 0) {
          pos += len;
          return true;
        }
        return false;
      }

      /**
       * @brief Utility function used to compare the json string with a regex token.
       * @param[in] str String that contains a regex to compare to the current parse point.
       * @returns @c true if the token matches; otherwise @c false.
       */
      bool is_regex_match(std::string const str) {
        // Ensures that the regex will match only the beginning of the substring.
        std::regex re(std::string("^") + str);

        // Run the regex on the string.
        std::smatch match;
        if(std::regex_search(json_.substr(pos), match, re)) {
          pos += size_t(match[0].length());
          return true;
        }
        return false;
      }

      /**
       * @brief Utility function used to eat whitespace.
       * @returns @c true always.
       */
      bool ignore_whitespace() {
        is_regex_match("\\s");
        return true;
      }

    private:
      std::string const& json_;
      size_t pos;
  };
}
