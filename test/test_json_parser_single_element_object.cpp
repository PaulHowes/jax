#include <jax.hpp>

int main() {
  std::string json = "{ \"first\" : 0 }";
  jax::json_parser p(json);
  return p.parse() ? 0 : 1;
}
