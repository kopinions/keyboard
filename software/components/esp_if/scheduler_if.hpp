#pragma once
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
};

template <typename... Args>
std::shared_ptr<scheduled> scheduler_if<Args...>::schedule(const std::string& id,
                                                           const kopinions::task<void(Args...)>& f, Args... args) {
  std::bind(f, std::forward<Args...>(args)...);

  auto tfunc = [](void* d) {
    auto& callback = *reinterpret_cast<kopinions::task<void(Args...)>*>(d);
    //    callback();
  };
  auto ptr = std::make_shared<scheduled_if>();

  const void* parameters = &f;

  xTaskCreate(tfunc, id.c_str(), 10000, const_cast<void*>(parameters), 1, &ptr->m_handle);

  return ptr;
}

void scheduled_if::cancel() { vTaskDelete(m_handle); }

}  // namespace kopinions