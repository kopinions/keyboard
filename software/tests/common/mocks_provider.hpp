#pragma once

//#include <boost/di.hpp>
#include "fakeit.hpp"

template<typename T>
auto& mock(bool reset=false) {
  static fakeit::Mock<T> mock;
  if (reset) {
    mock.Reset();
  }
  fakeit::When(Dtor(mock)).AlwaysDo([] {});

  return mock;
}

//class mocks_provider : public di::config {
//
//};
