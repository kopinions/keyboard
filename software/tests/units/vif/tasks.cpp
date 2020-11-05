#include "common/mocks_provider.hpp"
#include "vif.hpp"

namespace di = boost::di;
using namespace kopinions;
using namespace fakeit;
template <typename X>
auto fun() -> task<void(int)> {
  return [](int) -> void {
    []<class... Args>(type_traits::list<Args...>){

    }(typename type_traits::task_traits<X>::args{});
  };
}
int main() {
  "should_able_to_dispatch_the_task"_test = [] {
    auto injector = di::make_injector<mocks_provider>();
    auto&& sche = mock<scheduler<int>>();
    auto&& sched = mock<scheduled>();
    When(Method(sched, cancel)).AlwaysDo([]() {});
    sche.get().schedule(
        "xx", [](int) -> void { std::cout << "xxxx" << std::endl; }, 1);

    When(Method(sche, schedule)).AlwaysDo([](const std::string& id, auto&& a, auto c) -> std::shared_ptr<scheduled> {

    });
    auto&& creator = injector.create<std::shared_ptr<scheduler<>>>();
    bool called = false;
    int arg = 0;
    expect_that<int>(arg, matchers::eq(1));
  };
}