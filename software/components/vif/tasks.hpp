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
  constexpr task(T data) {
    invoke_ = invoke_impl<T>;
    destroy_ = destroy_impl<T>;
    data_ = new T{static_cast<T&&>(data)};
  }

  constexpr task(task&& other) noexcept {
    invoke_ = invoke_impl<decltype(other.invoke_)>;
    destroy_ = destroy_impl<decltype(other.destroy_)>;
    data_ = new decltype(other.data_){other.data_};
  }

  constexpr task(const task& other) {
    invoke_ = other.invoke_;
    destroy_ = other.destroy_;
    data_ = new decltype(other.data_){other.data_};
  };

  constexpr task(task&) = delete;

  constexpr task& operator=(const task& other) {
    invoke_ = other.invoke_;
    destroy_ = other.destroy_;
    data_ = new decltype(other.data_){other.data_};
    return *this;
  };

  constexpr task& operator=(task&& other) noexcept {
    invoke_ = invoke_impl<decltype(other.invoke_)>;
    destroy_ = destroy_impl<decltype(other.destroy_)>;
    data_ = new decltype(other.data_){other.data_};
    return *this;
  };

  ~task() { destroy_(data_); }

  [[nodiscard]] constexpr auto operator()(TArgs... args) -> R { return invoke_(data_, args...); }

  [[nodiscard]] constexpr auto operator()(TArgs... args) const -> R {
    return invoke_(data_, std::forward<TArgs...>(args)...);
  }

 private:
  template <typename T>
  static auto invoke_impl(void* data, TArgs... args) -> typename std::enable_if_t<!(std::is_void<R>::value), R> {
    return (*static_cast<T*>(data))(std::forward<TArgs...>(args)...);
  }

  template <typename T>
  static auto invoke_impl(void* data, TArgs... args) -> typename std::enable_if_t<std::is_void<R>::value, void> {
    (*static_cast<T*>(data))(std::forward<TArgs...>(args)...);
  }

  template <typename T>
  static auto destroy_impl(void* data) -> void {
    delete static_cast<T*>(data);
  }

 private:
  auto (*invoke_)(void*, TArgs...) -> R{};
  void (*destroy_)(void*){};
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

template <typename... Args>
class scheduler {
 public:
  virtual std::shared_ptr<scheduled> schedule(const std::string&, const kopinions::task<void(Args...)>&, Args...) = 0;
  virtual ~scheduler() = default;
};
};  // namespace kopinions