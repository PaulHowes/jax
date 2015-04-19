#include "test_json_parser_common.hpp"

int main() {
  std::string json = "\"string\"";
  if(parse(json)) {
    if(tokens.size() == 1 &&
        tokens[0].type() == jax::token_t::STRING_VALUE &&
        tokens[0].value() == "string") {
      return 0;
    }
  }
  return 1;
}

