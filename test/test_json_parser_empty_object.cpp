#include "test_json_parser_common.hpp"

int main() {
  std::string json = "{ }";
  if(parse(json)) {
    if(tokens.size() == 2 &&
        tokens[0].type() == jax::token_t::OBJECT_BEGIN &&
        tokens[1].type() == jax::token_t::OBJECT_END ) {
      return 0;
    }
  }
  return 1;
}

