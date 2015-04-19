#pragma once

#include <jax.hpp>
#include <functional>
#include <vector>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-prototypes"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#pragma clang diagnostic ignored "-Wglobal-constructors"

static std::vector<jax::token> tokens;

struct token_callback {
  void operator()(jax::token token) {
    tokens.push_back(token);
  }
};

bool parse(std::string const& json) {
  jax::json_parser p(json, token_callback());
  return p.parse();
}

#pragma clang diagnostic pop
