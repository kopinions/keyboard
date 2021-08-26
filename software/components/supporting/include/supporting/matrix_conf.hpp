#pragma once
#include <boost/di.hpp>

#include "keyboard/matrix.hpp"
namespace di = boost::di;
constexpr auto conf = [] {
  // col1-col15
  static const std::vector<kopinions::pin::id_t>& cols = std::vector<kopinions::pin::id_t>{
      kopinions::pin::id_t::IO2,  kopinions::pin::id_t::IO4,  kopinions::pin::id_t::IO5,  kopinions::pin::id_t::IO12,
      kopinions::pin::id_t::IO13, kopinions::pin::id_t::IO14, kopinions::pin::id_t::IO15, kopinions::pin::id_t::IO16,
      kopinions::pin::id_t::IO17, kopinions::pin::id_t::IO18, kopinions::pin::id_t::IO19, kopinions::pin::id_t::IO21,
      kopinions::pin::id_t::IO22, kopinions::pin::id_t::IO23, kopinions::pin::id_t::IO25,
  };

  // row1-row6
  static const std::vector<kopinions::pin::id_t>& rows = std::vector<kopinions::pin::id_t>{
      kopinions::pin::id_t::IO26, kopinions::pin::id_t::IO27, kopinions::pin::id_t::IO32,
      kopinions::pin::id_t::IO33, kopinions::pin::id_t::IO34, kopinions::pin::id_t::IO35,
  };

  static const kopinions::matrix_config object = kopinions::matrix_config{rows, cols, 4};
  return di::make_injector(di::bind<kopinions::matrix_config>.to(object));
};
