#pragma once
#include <boost/di.hpp>

#include "mocks_provider.hpp"
#include "vif.hpp"
namespace di = boost::di;
using namespace kopinions;
using namespace fakeit;

class fake_clk : public kopinions::clock {
 public:
  kopinions::time now() override { return kopinions::time(0); }
};

class fake_gpio : public kopinions::gpio {
 public:
  explicit fake_gpio(pin::status status) : m_status{status} {}
  pin::status current() override { return m_status; }
  void option(const pin::opt& opt) override {}
  void set(pin::status target) override {}
  ~fake_gpio() override = default;

 private:
  pin::status m_status;
};

class fake_gpios : public kopinions::gpios {
 public:
  gpio* select(pin::id p) override { return new fake_gpio(pin::status::HIGH); }
};

class fake_scheduled : public kopinions::scheduled {
 public:
  void cancel() override {}
};

template <typename... Args>
class fake_scheduler : public scheduler<Args...> {
 public:
  std::shared_ptr<scheduled> schedule(const std::string& id, const kopinions::task<void(Args...)>& f,
                                      Args... args) override;

 private:
  std::function<void()> closure;
  kopinions::task<void(Args...)> m_f;
};

template <typename... Args>
std::shared_ptr<scheduled> fake_scheduler<Args...>::schedule(const std::string& id,
                                                             const kopinions::task<void(Args...)>& f, Args... args) {
  m_f = f;
  closure = [this, &args...]() -> void { m_f(std::forward<Args...>(args)...); };
  auto tf = [](void* d) -> void { (*static_cast<decltype(closure)*>(d))(); };

  auto ptr = std::make_shared<fake_scheduled>();
  tf(&closure);

  return ptr;
}

class fake_sink : public kopinions::logging::sink {
 public:
  void consume(const logging::record& record) override { std::cout << record.message() << std::endl; }
};

constexpr auto fakes = [] {
  return di::make_injector(di::bind<kopinions::gpios>.to<fake_gpios>().in(di::singleton),
                           di::bind<kopinions::clock>.to<fake_clk>().in(di::singleton),
                           di::bind<kopinions::logging::sink>.to<fake_sink>().in(di::singleton),
                           di::bind<kopinions::scheduler<int>>.to<fake_scheduler<int>>().in(di::singleton),
                           di::bind<kopinions::logging::level>.to(kopinions::logging::level::DEBUG));
};

gpio* keep(pin::status s) { return new fake_gpio(s); }
