#pragma once
#include <sstream>
#include <string>

namespace kopinions {
class formatter {
 public:
  explicit formatter(std::string fmt) noexcept;

  template <typename... Args>
  std::string format(Args... args);

 private:
  std::string m_fmt;
};

class record;

class sink {
 public:
  virtual void consume(record&&) = 0;
};

class logger {
 public:
  enum level { DEBUG, INFO, WARN, ERROR, FATAL };
  logger(level root, std::shared_ptr<sink> sk) noexcept;

  template <typename... Args>
  void log(const level& lvl, std::string fmt, Args... args) const;

 private:
  level m_root;
  std::shared_ptr<sink> m_sink;
};

class record {
 public:
  template <typename... Args>
  record(logger::level lvl, formatter&& fmt, Args&&... args) noexcept;

  const logger::level& lvl() const;

  const std::string& message() const;

 private:
  logger::level m_lvl;
  std::string m_message;
};

formatter::formatter(std::string fmt) noexcept : m_fmt{fmt} {}

template <typename... Args>
std::string formatter::format(Args... args) {
  std::ostringstream sbuf;
  // fold expression
  ((sbuf << std::dec) << ... << args);
  return sbuf.str();
}

logger::logger(logger::level root, std::shared_ptr<sink> sk) noexcept : m_root{root}, m_sink{sk} {};

template <typename... Args>
void logger::log(const logger::level& lvl, std::string fmt, Args... args) const {
  // TODO consume when lvl >= root
  m_sink->consume(record{lvl, formatter{fmt}, std::forward<Args>(args)...});
}

template <typename... Args>
record::record(logger::level lvl, formatter&& fmt, Args&&... args) noexcept : m_lvl{lvl} {
  m_message = fmt.format(std::forward<Args>(args)...);
}
const logger::level& record::lvl() const { return m_lvl; }
const std::string& record::message() const { return m_message; }

}  // namespace kopinions
