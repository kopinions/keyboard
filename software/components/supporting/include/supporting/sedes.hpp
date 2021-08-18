#pragma once

#include <memory>
#include <vector>

#include "keyboard/key.hpp"

class sedes {
public:
    std::unique_ptr<char[]> serialize(const std::vector<kopinions::key_t> &);
};