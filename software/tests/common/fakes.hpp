#pragma once
#include <boost/di.hpp>

#include "common/mocks_provider.hpp"
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
  std::shared_ptr<gpio> select(const pin::id& p) override { return std::make_shared<fake_gpio>(pin::status::HIGH); }
};

class fake_scheduled : public kopinions::scheduled {
 public:
  void cancel() override {}
};

template <typename... Args>
class fake_scheduler : public kopinions::scheduler<Args...> {
 public:
  std::shared_ptr<scheduled> schedule(const std::string& id, kopinions::task<void(Args...)> f, Args... args) override {
    auto tfunc = [](void* d) {
      auto& callback = *reinterpret_cast<kopinions::task<void(void)>*>(d);
      callback();
    };
    std::bind(f, std::forward<Args...>(args)...);

    tfunc(&f);
    return std::make_shared<fake_scheduled>();
  }
};

class fake_sink : public kopinions::sink {
 public:
  void consume(record&& record) override { std::cout << record.message() << std::endl; }
};

constexpr auto fakes = [] {
  return di::make_injector(
      di::bind<gpios>.to<fake_gpios>().in(di::singleton), di::bind<kopinions::clock>.to<fake_clk>().in(di::singleton),
      di::bind<scheduler<>>.to<fake_scheduler<>>().in(di::singleton), di::bind<sink>.to<fake_sink>().in(di::singleton),
      di::bind<logger::level>.to(logger::level::DEBUG));
};

std::shared_ptr<gpio> keep(pin::status s) { return std::shared_ptr<fake_gpio>(new fake_gpio(s)); }
