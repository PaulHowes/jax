#include "test_json_parser_common.hpp"

int main() {
  std::string json = "{ \"first\" : 1, \"second\" : 2, \"third\" : 3 }";
  if(parse(json)) {
    if(tokens.size() == 8 &&
        tokens[0].type()  == jax::token_t::OBJECT_BEGIN &&
        tokens[1].type()  == jax::token_t::OBJECT_KEY &&
        tokens[1].value() == "first" &&
        tokens[2].type()  == jax::token_t::NUMBER_VALUE &&
        tokens[2].value() == "1" &&
        tokens[3].type()  == jax::token_t::OBJECT_KEY &&
        tokens[3].value() == "second" &&
        tokens[4].type()  == jax::token_t::NUMBER_VALUE &&
        tokens[4].value() == "2" &&
        tokens[5].type()  == jax::token_t::OBJECT_KEY &&
        tokens[5].value() == "third" &&
        tokens[6].type()  == jax::token_t::NUMBER_VALUE &&
        tokens[6].value() == "3" &&
        tokens[7].type()  == jax::token_t::OBJECT_END ) {
      return 0;
    }
  }
  return 1;
}
