#pragma once
#include <iostream>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "tasks.hpp"

namespace kopinions {
template <typename...>
class scheduler_if;

class scheduled_if : public scheduled {
 public:
  template <typename...>
  friend class scheduler_if;

 private:
  TaskHandle_t m_handle;

 public:
  void cancel() override;
};

template <typename... Args>
class scheduler_if : public scheduler<Args...> {
 public:
  std::shared_ptr<scheduled> schedule(const std::string& id, const kopinions::task<void(Args...)>& f,
                                      Args... args) override;

 private:
  std::function<void()> closure;
  kopinions::task<void(Args...)> m_f;
};

template <typename... Args>
std::shared_ptr<scheduled> scheduler_if<Args...>::schedule(const std::string& id,
                                                           const kopinions::task<void(Args...)>& f, Args... args) {
  m_f = f;

  closure = [this, &args...]() -> void { m_f(std::forward<Args...>(args)...); };
  auto tf = [](void* d) -> void { (*static_cast<decltype(closure)*>(d))(); };

  auto ptr = std::make_shared<scheduled_if>();

  xTaskCreate(tf, id.c_str(), 10000, &closure, 1, &ptr->m_handle);

  return ptr;
}

void kopinions::scheduled_if::cancel() { vTaskDelete(m_handle); }
}  // namespace kopinions