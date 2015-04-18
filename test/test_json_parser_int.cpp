#include <jax.hpp>

int main() {
  std::string json = "12345";
  jax::json_parser p(json);
  return p.parse() ? 0 : 1;
}

