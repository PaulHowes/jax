#include "test_json_parser_common.hpp"

int main() {
  std::string json = "{ \"first\" : 0 }";
  if(parse(json)) {
    if(tokens.size() == 4 &&
        tokens[0].type()  == jax::token_t::OBJECT_BEGIN &&
        tokens[1].type()  == jax::token_t::OBJECT_KEY &&
        tokens[1].value() == "first" &&
        tokens[2].type()  == jax::token_t::NUMBER_VALUE &&
        tokens[2].value() == "0" &&
        tokens[3].type()  == jax::token_t::OBJECT_END ) {
      return 0;
    }
  }
  return 1;
}
