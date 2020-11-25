#pragma once
#include "matrix.hpp"
// row1-row6
static const auto rows = std::vector<pin::id>{pin::id::IO26, pin::id::IO27, pin::id::IO32, pin::id::IO33};

// col1-col15
static const auto cols = std::vector<pin::id>{
    pin::id::IO2,  pin::id::IO4,  pin::id::IO5,  pin::id::IO12, pin::id::IO13,
    pin::id::IO14, pin::id::IO15, pin::id::IO16, pin::id::IO17, pin::id::IO18,
    pin::id::IO19, pin::id::IO21, pin::id::IO22, pin::id::IO23, pin::id::IO25,
};
namespace di = boost::di;
constexpr auto conf = []() {

  return di::make_injector(di::bind<matrix_config>.to(matrix_config(rows, cols, 4)))[di::override];
};
