#include "test_json_parser_common.hpp"

int main() {
  std::string json = ".99999";
  if(parse(json)) {
    if(tokens.size() == 1 &&
        tokens[0].type() == jax::token_t::NUMBER_VALUE &&
        tokens[0].value() == json) {
      return 0;
    }
  }
  return 1;
}

