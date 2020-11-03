#include "common/mocks_provider.hpp"
#include "vif.hpp"

namespace di = boost::di;
using namespace kopinions;
using namespace fakeit;

int main() {
  "should_able_to_dispatch_the_task"_test = [] {
    auto injector = di::make_injector<mocks_provider>();
    auto&& sche = mock<scheduler>();
    auto&& sched = mock<scheduled>();
    When(Method(sched, cancel)).AlwaysDo([]() {});

    When(Method(sche, schedule)).AlwaysDo([&sched](const std::string& id, std::function<void(void)> f) {
      auto tfunc = [](void* d) {
        auto& callback = *reinterpret_cast<std::function<void(void)>*>(d);
        callback();
      };
      tfunc(&f);
      return std::shared_ptr<scheduled>();
    });
    auto&& creator = injector.create<std::shared_ptr<tasks>>();
    bool called = false;
    int arg = 0;
    auto&& created = creator->create("test", std::function<void(int)>{[&called, &arg](int a) {
                                       called = true;
                                       arg = a;
                                     }});
    auto&& dispat = injector.create<std::shared_ptr<dispatcher>>();
    dispat->dispatch<int>(created, 1);
    expect_that<bool>(called, matchers::eq(true));
    expect_that<int>(arg, matchers::eq(1));
  };
}