#pragma once

//#include <boost/di.hpp>
#include "fakeit.hpp"

template<typename T>
auto& mock(bool reset=false) {
  using namespace fakeit;
  static Mock<T> mock;
  if (reset) {
    mock.Reset();
  }
  When(Dtor(mock)).AlwaysDo([] {});

  return mock;
}

//class mocks_provider : public di::config {
//
//};
