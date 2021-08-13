#pragma once
#include "vif/tasks.hpp"
//
// template <template <typename, typename> typename container_type, typename value_type, typename option>
// class selector {
// public:
//  virtual std::optional<value_type> select(const container_type<value_type, Allocator>&) = 0;
//};

class reporter {
 private:
  task<void()>* m_runnable;

 public:
  reporter() {
    //    m_runnable = new task<void()>{[]() {
    //      while (true) {
    //        std::cout << "test" << std::endl;
    //      }
    //    }};
  }
  task<void()>& runnable() { return *m_runnable; };
};