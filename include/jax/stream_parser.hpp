/**
 * @file stream_parser.hpp
 * @brief Implements a stream-based JSON parser.
 */

#pragma once

#include <jax/json_parser.hpp>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#include <any.hpp>
#pragma clang diagnostic pop

#include <memory>
using std::placeholders::_1;

#include <string>

/**
 * @namespace jax
 */
namespace jax {
  template<typename T> class stream_parser {
    public:
      stream_parser(std::string const& json) :
          self_(static_cast<T*>(this)),
          parser_(new jax::json_parser(json, std::bind(&stream_parser<T>::callback, this, _1))) {
      }

      bool parse() {
        return parser_->parse();
      }

    public:
      void on_value(type::any&) { }
      void on_array_begin() { }
      void on_array_end() { }
      void on_object_begin() { }
      void on_object_key(std::string&) { }
      void on_object_end() { }

    private:
      void callback(jax::token t) {
        switch(t.type()) {
          case token_t::NULL_VALUE:
            self_->on_value(type::any(nullptr));
            break;
          case token_t::BOOLEAN_VALUE:
            if(t.value() == "true") {
              self_->on_value(type::any(true));
            }
            else {
              self_->on_value(type::any(false));
            }
            break;
          case token_t::NUMBER_VALUE:
            self_->on_value(type::any(std::stod(t.value())));
            break;
          case token_t::STRING_VALUE:
            self_->on_value(type::any(t.value()));
            break;
          case token_t::ARRAY_BEGIN:
            self_->on_array_begin();
            break;
          case token_t::ARRAY_END:
            self_->on_array_end();
            break;
          case token_t::OBJECT_BEGIN:
            self_->on_object_begin();
            break;
          case token_t::OBJECT_KEY:
            self_->on_object_key(t.value());
            break;
          case token_t::OBJECT_END:
            self_->on_object_end();
            break;
        }
      }

      T* self_;

      std::unique_ptr<jax::json_parser> parser_;
  };
}
