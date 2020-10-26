
#include "gpio_if.hpp"

gpio_if::~gpio_if() {}
pin::status gpio_if::current() { return pin::status::HIGH; }
void gpio_if::option(const pin::opt& opt) {}
void gpio_if::set(pin::status target) {}
