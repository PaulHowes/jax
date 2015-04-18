#include <jax.hpp>

int main() {
  std::string json = "[ 0, 1, 2 ]";
  jax::json_parser p(json);
  return p.parse() ? 0 : 1;
}
