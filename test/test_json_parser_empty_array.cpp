#include <jax.hpp>

int main() {
  std::string json = "[ ]";
  jax::json_parser p(json);
  return p.parse() ? 0 : 1;
}
