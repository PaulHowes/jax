/**
 * @file tokens.hpp
 * @brief Defines all possible tokens found during parsing.
 */

#pragma once

#include <string>

/**
 * @namespace jax
 */
namespace jax {
  enum class token_t {
    NULL_VALUE,
    BOOLEAN_VALUE,
    NUMBER_VALUE,
    STRING_VALUE,
    ARRAY_BEGIN,
    ARRAY_END,
    OBJECT_BEGIN,
    OBJECT_END,
    OBJECT_KEY
  };

  class token {
    public:
      token(token_t type, std::string const& value) : type_(type), value_(value) {
      }

      token_t type() const {
        return type_;
      }

      std::string value() const {
        return value_;
      }

    private:
      token_t type_;
      int padding_;
      std::string value_;
  };
}
