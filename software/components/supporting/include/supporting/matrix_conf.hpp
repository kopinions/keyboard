#pragma once
#include <boost/di.hpp>

#include "keyboard/matrix.hpp"
namespace di = boost::di;
constexpr auto conf = []() {
  // col1-col15
  const std::vector<pin::id>& row = std::vector<pin::id>{
      pin::id::IO2,  pin::id::IO4,  pin::id::IO5,  pin::id::IO12, pin::id::IO13,
      pin::id::IO14, pin::id::IO15, pin::id::IO16, pin::id::IO17, pin::id::IO18,
      pin::id::IO19, pin::id::IO21, pin::id::IO22, pin::id::IO23, pin::id::IO25,
  };

  // row1-row6
  const std::vector<pin::id>& col = std::vector<pin::id>{
      pin::id::IO26, pin::id::IO27, pin::id::IO32, pin::id::IO33,
      // TODO: find another pin to replace these two column
      //      pin::id::IO34,
      //      pin::id::IO35,
  };
  return di::make_injector(di::bind<matrix_config>()(row, col, 4)[di::override]);
};
