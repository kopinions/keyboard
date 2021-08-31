#pragma once

#include <boost/di.hpp>

#include "fakeit.hpp"
namespace di = boost::di;

template <typename T>
auto& mock(bool reset = false) {
  using namespace fakeit;
  static Mock<T> mock;
  if (reset) {
    mock.Reset();
  }
  When(Dtor(mock)).AlwaysDo([] {});

  return mock;
}

class mocks_provider : public di::config {
 public:
  class mock_provider {
   public:
    template <class...>
    struct is_creatable {
      static constexpr auto value = true;
    };

    template <class T, class TInitialization, class TMemory, class... TArgs>
    std::enable_if_t<!std::is_polymorphic<T>::value, T*> get(const TInitialization&, const TMemory&,
                                                             TArgs&&... args) const {
      return new T{std::forward<TArgs>(args)...};
    }

    template <class T, class TInitialization, class TMemory, class... TArgs>
    std::enable_if_t<std::is_polymorphic<T>::value, T*> get(const TInitialization&, const TMemory&,
                                                            TArgs&&... args) const {
      return &mock<T>(false).get();
    }

    template <class T, class... TArgs>
    auto get(const di::type_traits::direct&, const di::type_traits::stack&, TArgs&&... args) const noexcept {
      return T(std::forward<TArgs&&>(args)...);
    }

    template <class T, class... TArgs>
    auto get(const di::type_traits::uniform&, const di::type_traits::stack&, TArgs&&... args) const noexcept {
      return T{std::forward<TArgs&&>(args)...};
    }

    template <class T, class... TArgs>
    auto get(const di::type_traits::direct&, const di::type_traits::heap&, TArgs&&... args) {
      return new T(std::forward<TArgs&&>(args)...);
    }
  };

 public:
  static auto provider(...) noexcept { return mock_provider{}; }
};