/**
 * @file json_parser.hpp
 * @brief Hand-coded, general-puropse JSON parser.
 */

#pragma once

#include <jax/tokens.hpp>
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
      json_parser(std::string const& json) : callback_([](jax::token){}), json_(json) {
      }

      /**
       * @brief Initializes a new jax::json_parser with the JSON text to parse.
       * @param[in] json JSON text to parse.
       */
      json_parser(std::string const& json, std::function<void(jax::token)> callback)
          : callback_(callback), json_(json) {
      }

      /**
       * @brief Parses the input string.
       */
      bool parse() {
        pos_ = 0;
        return is_value();
      }

    protected:
      /**
       * @brief Used to determine whether the next token is a valid Javascript value.
       * @returns @c true if the next token is a valid Javascript value; otherwise @c false.
       */
      bool is_value() {
        return is_null()   ||
               is_true()   ||
               is_false()  ||
               is_number() ||
               is_string() ||
               is_array()  ||
               is_object();
      }

      /**
       * @brief Used to determine whether the next token is "null".
       * @returns @c true if the next token is "null"; otherwise @c false.
       */
      bool is_null() {
        if(is_match("null")) {
          callback_(token(token_t::NULL_VALUE, "null"));
          return true;
        }

        return false;
      }

      /**
       * @brief Used to determine whether the next token is "true".
       * @returns @c true if the next token is "true"; otherwise @c false.
       */
      bool is_true() {
        if(is_match("true")) {
          callback_(token(token_t::BOOLEAN_VALUE, "true"));
          return true;
        }

        return false;
      }

      /**
       * @brief Used to determine whether the next token is "false".
       * @returns @c true if the next token is "false"; otherwise @c false.
       */
      bool is_false() {
        if(is_match("false")) {
          callback_(token(token_t::BOOLEAN_VALUE, "false"));
          return true;
        }

        return false;
      }

      /**
       * @brief Used to determine whether the next token is a number.
       * @returns @c true if the next token is a number; otherwise @c false.
       */
      bool is_number() {
        std::string matched;
        if(is_regex_match("[-+]?[0-9]*\\.?[0-9]+(?:[eE][-+]?[0-9]+)?", matched)) {
          callback_(token(token_t::NUMBER_VALUE, matched));
          return true;
        }

        return false;
      }

      /**
       * @brief Used to determine whether the next token is a string.
       * @returns @c true if the next token is a string; otherwise @c false.
       */
      bool is_string() {
        std::string matched;
        if(is_regex_match("\"(.*?)\"", matched)) {
          callback_(token(token_t::STRING_VALUE, matched));
          return true;
        }

        return false;
      }

      /**
       * @brief Used to determine whether the next token is an object key.
       * @returns @c true if the next token is an object key; otherwise @c false.
       */
      bool is_object_key() {
        std::string matched;
        if(is_regex_match("\"(.*?)\"", matched)) {
          callback_(token(token_t::OBJECT_KEY, matched));
          return true;
        }

        return false;
      }

      /**
       * @brief Used to determine whether the next token begins an array.
       * @returns @c true if the next token begins an array; otherwise @c false.
       */
      bool is_array_begin() {
        if(is_match("[")) {
          callback_(token(token_t::ARRAY_BEGIN, "["));
          return true;
        }

        return false;
      }

      /**
       * @brief Used to determine whether the next token ends an array.
       * @returns @c true if the next token ends an array; otherwise @c false.
       */
      bool is_array_end() {
        if(is_match("]")) {
          callback_(token(token_t::ARRAY_END, "]"));
          return true;
        }

        return false;
      }

      /**
       * @brief Used to determine whether the next token begins an object.
       * @returns @c true if the next token begins an object; otherwise @c false.
       */
      bool is_object_begin() {
        if(is_match("{")) {
          callback_(token(token_t::OBJECT_BEGIN, "{"));
          return true;
        }

        return false;
      }

      /**
       * @brief Used to determine whether the next token ends an object.
       * @returns @c true if the next token ends an object; otherwise @c false.
       */
      bool is_object_end() {
        if(is_match("}")) {
          callback_(token(token_t::OBJECT_END, "}"));
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
        if(!is_array_begin()) {
          return false;
        }

        ignore_whitespace();

        // If the next token is a right square-brace then this is an empty array.
        if(is_array_end()) {
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
        if(is_array_end()) {
          return true;
        }

        return false;
      }

      /**
       * @brief Used to determine whether the next token is an object.
       * @returns @c true if the next token is an object; otherwise @c false.
       */
      bool is_object() {
        // Punt if the first character isn't a left curly-brace.
        if(!is_object_begin()) {
          return false;
        }

        ignore_whitespace();

        // If the next token is a right curly-brace then this is an empty object.
        if(is_object_end()) {
          return true;
        }

        // The next three tokens must be string + ":" + value.
        if(!(is_object_key() &&
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
          if(!(is_object_key() &&
               ignore_whitespace() &&
               is_match(":") &&
               ignore_whitespace() &&
               is_value())) {
            return false;
          }

          ignore_whitespace();
        }

        // The final token must be a right curly-brace.
        if(is_object_end()) {
          return true;
        }

        return false;
      }

      /**
       * @brief Utility function used to compare strings.
       * @param[in] str String to find at the current parse point.
       * @returns @c true if the token matches; otherwise @c false.
       */
      bool is_match(std::string const& str) {
        size_t len = str.length();
        if(json_.substr(pos_, len).compare(str) == 0) {
          pos_ += len;
          return true;
        }
        return false;
      }

      /**
       * @brief Utility function used to compare the json string with a regex token.
       * @param[in] str String that contains a regex to compare to the current parse point.
       * @returns @c true if the token matches; otherwise @c false.
       */
      bool is_regex_match(std::string const str, std::string& matched) {
        // Ensures that the regex will match only the beginning of the substring.
        std::regex re(std::string("^") + str);

        // Run the regex on the string.
        std::smatch match;
        if(std::regex_search(json_.substr(pos_), match, re)) {
          pos_ += size_t(match[0].length());
          // HACK: returns the last capture group instead of the entire match. This allows strings
          // to be returned without the surrounding quotation marks, but everything else (e.g.
          // numbers) to return in their entirety as there is no capture group.
          matched = match[match.size() - 1];
          return true;
        }

        return false;
      }

      /**
       * @brief Utility function used to eat whitespace.
       * @returns @c true always.
       */
      bool ignore_whitespace() {
        std::string matched;
        is_regex_match("\\s*", matched);
        return true;
      }

    private:
      std::function<void(jax::token)> callback_;
      std::string const& json_;
      size_t pos_;
  };
}
