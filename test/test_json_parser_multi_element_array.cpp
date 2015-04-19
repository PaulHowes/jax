#include "test_json_parser_common.hpp"

int main() {
  std::string json = "[ 0, 1, 2 ]";
  if(parse(json)) {
    if(tokens.size() == 5 &&
        tokens[0].type()  == jax::token_t::ARRAY_BEGIN &&
        tokens[1].type()  == jax::token_t::NUMBER_VALUE &&
        tokens[1].value() == "0" &&
        tokens[2].type()  == jax::token_t::NUMBER_VALUE &&
        tokens[2].value() == "1" &&
        tokens[3].type()  == jax::token_t::NUMBER_VALUE &&
        tokens[3].value() == "2" &&
        tokens[4].type()  == jax::token_t::ARRAY_END ) {
      return 0;
    }
  }
  return 1;
}
