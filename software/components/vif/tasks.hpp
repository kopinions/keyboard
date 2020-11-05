#pragma once
#include <functional>
namespace kopinions {

template <class>
struct task;

template <class R, class... TArgs>
struct task<R(TArgs...)> {
 public:
  constexpr task() = default;

  template <typename T>
  constexpr task(T data) : invoke_{invoke_impl<T>}, destroy_{destroy_impl<T>}, data_{new T{static_cast<T&&>(data)}} {}

  constexpr task(task&& other)
      : invoke_{static_cast<decltype(other.invoke_)&&>(other.invoke_)},
        destroy_{static_cast<decltype(other.destroy_)&&>(other.destroy_)},
        data_{static_cast<decltype(other.data_)&&>(other.data_)} {
    other.data_ = {};
  }

  constexpr task(const task& other)
      : invoke_{static_cast<decltype(other.invoke_)>(other.invoke_)},
        destroy_{static_cast<decltype(other.destroy_)>(other.destroy_)},
        data_{static_cast<decltype(other.data_)>(other.data_)} {}
  constexpr task& operator=(const task&) = delete;
  constexpr task& operator=(task&&) = delete;
  ~task() { destroy_(data_); }

  [[nodiscard]] constexpr auto operator()(TArgs... args) -> R { return invoke_(data_, args...); }
  [[nodiscard]] constexpr auto operator()(TArgs... args) const -> R { return invoke_(data_, args...); }

 private:
  template <typename T>
  constexpr static auto invoke_impl(void* data, TArgs... args) {
    return (*static_cast<T*>(data))(args...);
  };

  template <typename T>
  constexpr static void destroy_impl(void* data) {
    delete static_cast<T*>(data);
  }

 private:
  R (*invoke_)(void*, TArgs...);
  void (*destroy_)(void*);

  void* data_{};
};

namespace type_traits {
template <class...>
struct list {};

template <class T, class...>
struct identity {
  using type = T;
};

template <class T>
struct task_traits : task_traits<decltype(&T::operator())> {};

template <class R, class... TArgs>
struct task_traits<R (*)(TArgs...)> {
  using result_type = R;
  using args = list<TArgs...>;
};

template <class R, class... TArgs>
struct task_traits<R(TArgs...)> {
  using result_type = R;
  using args = list<TArgs...>;
};

template <class R, class T, class... TArgs>
struct task_traits<R (T::*)(TArgs...)> {
  using result_type = R;
  using args = list<TArgs...>;
};

template <class R, class T, class... TArgs>
struct task_traits<R (T::*)(TArgs...) const> {
  using result_type = R;
  using args = list<TArgs...>;
};
}  // namespace type_traits

class scheduled {
 public:
  virtual void cancel() = 0;
  virtual ~scheduled() = default;
};

class ischeduler {};

template <typename... Args>
class scheduler : public ischeduler {
 public:
  virtual std::shared_ptr<scheduled> schedule(const std::string&, const kopinions::task<void(Args...)>&, Args...) = 0;
  virtual ~scheduler() = default;
};
};  // namespace kopinions