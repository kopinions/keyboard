#pragma once
#include <iostream>
#include <type_traits>
namespace kopinions {
template <typename T>
inline std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream,
                                const T& e) {
  return stream << static_cast<typename std::underlying_type<T>::type>(e);
}
};  // namespace kopinions
