#pragma once
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

namespace kopinions::logging {
enum class level { DEBUG, INFO, WARN, ERROR, FATAL };
class formatter {
 public:
  explicit formatter(std::string fmt) noexcept : m_fmt{std::move(fmt)} {};

  template <typename... Args>
  std::string format(Args... args) const {
    std::ostringstream sbuf;
    // fold expression
    ((sbuf << std::dec) << ... << args);
    return sbuf.str();
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
  logger(level root, std::shared_ptr<sink> sk) noexcept : m_root{root}, m_sink{sk} {};

  template <typename... Args>
  void log(const level& lvl, const std::string& fmt, Args... args) const {
    // TODO consume when lvl >= root
    m_sink->consume(record(lvl, formatter{fmt}, std::forward<Args>(args)...));
  };

 private:
  level m_root;
  std::shared_ptr<sink> m_sink;
};

}  // namespace kopinions::logging
