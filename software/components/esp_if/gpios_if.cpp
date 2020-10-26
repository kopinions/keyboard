#include "gpios_if.hpp"

#include <memory>

#include "gpio_if.hpp"
#include "pin.hpp"

std::shared_ptr<gpio> gpios_if::select(const pin::id& p) { return std::shared_ptr<gpio_if>(); }
gpios_if::~gpios_if() {}