#include <jax.hpp>

int main() {
  std::string json = "{ \"first\" : 1, \"second\" : 2, \"third\" : 3 }";
  jax::json_parser p(json);
  return p.parse() ? 0 : 1;
}
