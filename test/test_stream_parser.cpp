#include <jax.hpp>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wfloat-equal"
#pragma clang diagnostic ignored "-Wpadded"

class test_parser : public jax::stream_parser<test_parser> {
  public:
    test_parser(std::string const& json) : jax::stream_parser<test_parser>(json), counter_(-1) {
    }
    void on_object_key(std::string const& key) {
      ++counter_;
      if(key != keys_[counter_]) {
        throw;
      }
    }
    void on_value(type::any const& value) {
      if(value.as<double>() != values_[counter_]) {
        throw;
      }
    }
  private:
    int counter_;
    std::string keys_[3] = { "first", "second", "third" };
    double values_[3] = { 1, 2, 3 };
};

#pragma clang diagnostic pop

int main() {
  std::string json = "{ \"first\" : 1, \"second\" : 2, \"third\" : 3 }";
  test_parser p(json);
  return p.parse() ? 0 : 1;
}

