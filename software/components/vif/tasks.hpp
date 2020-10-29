#pragma once
#include <functional>
namespace kopinions {
template <typename... Args>
class task {
 public:
  task(std::string name, std::function<void(Args...)> f)
      : m_f{f} {

        };

  void undertaken(Args... args) { m_f(std::forward<Args>(args)...); };

 private:
  std::function<void(Args...)> m_f;
};

class schedule {
 public:
  void cancel() {}
};

class scheduler {
 public:
  template <typename... Args>
  schedule taken(std::shared_ptr<task<Args...>> t, Args... args) {
    t->undertaken(std::forward<Args>(args)...);
    return schedule{};
  };
};

class tasks {
 public:
  template <typename... Args>
  std::shared_ptr<task<Args...>> create(std::string name, std::function<void(Args...)> f) {
    return std::make_shared<task<Args...>>(name, f);
  };
};
};  // namespace kopinions