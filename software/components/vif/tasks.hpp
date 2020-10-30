#pragma once
#include <functional>
namespace kopinions {
template <typename... Args>
class task {
 public:
  task(std::string name, std::function<void(Args...)> f) : m_f{f}, m_name{name} {};

  const std::string& id() const { return m_name; }

  void undertaken(Args... args) { m_f(std::forward<Args>(args)...); };

 private:
  std::function<void(Args...)> m_f;
  std::string m_name;
};

class scheduled {
 public:
  virtual void cancel() = 0;
};

class scheduler {
 public:
  virtual std::shared_ptr<scheduled> schedule(const std::string& id, std::function<void(void)> f) = 0;
};

class dispatcher {
 public:
  dispatcher(std::shared_ptr<scheduler> sc) : m_sc{sc} {}
  template <typename... Args>
  std::shared_ptr<scheduled> dispatch(std::shared_ptr<task<Args...>> t, Args... args) {
    return m_sc->schedule(t->id(),
                          std::function<void(void)>{[&args..., t]() { t->undertaken(std::forward<Args>(args)...); }});
  }

 private:
  std::shared_ptr<scheduler> m_sc;
};

class tasks {
 public:
  template <typename... Args>
  std::shared_ptr<task<Args...>> create(std::string name, std::function<void(Args...)> f) {
    return std::make_shared<task<Args...>>(name, f);
  };
};
};  // namespace kopinions