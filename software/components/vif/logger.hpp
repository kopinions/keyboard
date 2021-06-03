#pragma once
#include <cstdio>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>

namespace kopinions::logging {
enum class level { DEBUG, INFO, WARN, ERROR, FATAL };
class formatter {
 public:
  explicit formatter(std::string fmt) noexcept : m_fmt{std::move(fmt)} {};

  template <typename... Args>
  std::string format(Args... args) const {
    int size_s = std::snprintf(nullptr, 0, m_fmt.c_str(), args...) + 1;  // Extra space for '\0'
    if (size_s <= 0) {
      throw std::runtime_error("Error during formatting.");
    }
    auto size = static_cast<size_t>(size_s);
    auto buf = std::make_unique<char[]>(size);
    std::snprintf(buf.get(), size, m_fmt.c_str(), args...);
    return std::string(buf.get(), buf.get() + size - 1);  // We don't want the '\0' inside
  };

 private:
  std::string m_fmt;
};

class record {
 public:
  template <typename... Args>
  record(level lvl, const formatter& fmt, Args&&... args) noexcept : m_lvl{lvl} {
    m_message = fmt.format(std::forward<Args>(args)...);
  };

  [[nodiscard]] const level& lvl() const { return m_lvl; };

  [[nodiscard]] const std::string& message() const { return m_message; };

 private:
  level m_lvl;
  std::string m_message;
};

class sink {
 public:
  virtual void consume(const record&) = 0;
  virtual ~sink() = default;
};

class logger {
 public:
  logger(level root, sink* sk) noexcept : m_root{root}, m_sink{sk} {};

  template <typename... Args>
  void log(const level& lvl, const std::string& fmt, Args... args) const {
    // TODO consume when lvl >= root
    m_sink->consume(record(lvl, formatter{fmt}, std::forward<Args>(args)...));
  };

  template <typename... Args>
  void info(const std::string& fmt, Args... args) const {
    // TODO consume when lvl >= root
    m_sink->consume(record(level::INFO, formatter{fmt}, std::forward<Args>(args)...));
  };

  template <typename... Args>
  void error(const std::string& fmt, Args... args) const {
    // TODO consume when lvl >= root
    m_sink->consume(record(level::ERROR, formatter{fmt}, std::forward<Args>(args)...));
  };

  template <typename... Args>
  void debug(const std::string& fmt, Args... args) const {
    // TODO consume when lvl >= root
    m_sink->consume(record(level::DEBUG, formatter{fmt}, std::forward<Args>(args)...));
  };

  template <typename... Args>
  void warn(const std::string& fmt, Args... args) const {
    // TODO consume when lvl >= root
    m_sink->consume(record(level::WARN, formatter{fmt}, std::forward<Args>(args)...));
  };

 private:
  level m_root;
  sink* m_sink;
};

}  // namespace kopinions::logging
