#include <jax.hpp>

int main() {
  std::string json = ".99999";
  jax::json_parser p(json);
  return p.parse() ? 0 : 1;
}

