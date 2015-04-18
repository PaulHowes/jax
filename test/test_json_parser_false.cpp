#include <jax.hpp>

int main() {
  std::string json = "false";
  jax::json_parser p(json);
  return p.parse() ? 0 : 1;
}
