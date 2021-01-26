#pragma once

template <typename T>
class ibuilder {
 public:
  virtual T build() = 0;
  virtual ~ibuilder() = default;
};