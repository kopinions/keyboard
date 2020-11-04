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

class fake_gpios : public kopinions::gpios {
 public:
  std::shared_ptr<gpio> select(const pin::id& p) override { return std::shared_ptr<gpio>(); }
};

class fake_scheduler : public kopinions::scheduler {
 public:
  std::shared_ptr<scheduled> schedule(const std::string& id, std::function<void(void)> f) override {
    return std::shared_ptr<scheduled>();
  }
};

class fake_sink : public kopinions::sink {
 public:
  void consume(record&& record) override {}
};

constexpr auto fakes = [] {
  return di::make_injector(
      di::bind<gpios>.to<fake_gpios>().in(di::singleton), di::bind<kopinions::clock>.to<fake_clk>().in(di::singleton),
      di::bind<scheduler>.to<fake_scheduler>().in(di::singleton), di::bind<sink>.to<fake_sink>().in(di::singleton),
      di::bind<logger::level>.to(logger::level::DEBUG));
};
