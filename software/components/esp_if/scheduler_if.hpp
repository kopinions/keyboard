#pragma once
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "tasks.hpp"

namespace kopinions {
class scheduler_if;
class scheduled_if : public scheduled {
 public:
  friend class scheduler_if;

 private:
  TaskHandle_t m_handle;

 public:
  void cancel() override;
};
class scheduler_if : public scheduler {
 public:
  std::shared_ptr<scheduled> schedule(const std::string& id, std::function<void(void)> f) override;

 private:
};

void scheduled_if::cancel() { vTaskDelete(m_handle); }

std::shared_ptr<scheduled> scheduler_if::schedule(const std::string& id, std::function<void(void)> f) {
  auto tfunc = [](void* d) {
    auto& callback = *reinterpret_cast<std::function<void(void)>*>(d);
    callback();
  };
  auto ptr = std::make_shared<scheduled_if>();

  xTaskCreate(tfunc, id.c_str(), 10000, &f, 1, &ptr->m_handle);

  return ptr;
}
}  // namespace kopinions