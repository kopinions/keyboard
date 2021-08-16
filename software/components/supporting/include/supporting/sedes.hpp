#pragma once
#include <memory>
#include <vector>
class sedes {
  std::unique_ptr<char*> serialize(std::vector<key_t>& const);
};
