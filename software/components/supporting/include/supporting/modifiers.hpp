#include <boost/di.hpp>

#include "keyboard/modifier.hpp"
namespace di = boost::di;
const static std::map<kopinions::key_t::id_t, kopinions::key_t::id_t> fn_modifier_table = {
    {F1, PLAY},
    {FN, NONE},
};
constexpr auto modifiers = [] {
  return di::make_injector(
      di::bind<std::map<kopinions::key_t::id_t, kopinions::key_t::id_t>>.to());
};