#include "keyboard.hpp"

#include <memory>

#include "gpios.hpp"

class fake_gpio : public gpio {
 public:
  fake_gpio() = default;
  pin::status current() override { return pin::status(); }
  void set(pin::status target) override {}
};

class fake_gpios : public gpios {
 public:
  explicit fake_gpios(){

  };

  std::shared_ptr<gpio> open(const pin& p, const pin::opt& opt) override { return std::make_shared<fake_gpio>(); }
};

int main() {
  "dummy"_test = [] {
    std::shared_ptr<fake_gpios> sharedPtr;
    sharedPtr = std::make_shared<fake_gpios>();
    keyboard kbd{sharedPtr};
    expect(true);
  };
}