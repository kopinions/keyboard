#pragma once
#include <sstream>
#include <string>

namespace kopinions {

template <typename T>
inline std::ostream& operator<<(typename std::enable_if<std::is_enum<T>::value, std::ostream>::type& stream,
                                const T& e) {
  return stream << static_cast<typename std::underlying_type<T>::type>(e);
}

class formatter {
 public:
  formatter(std::string fmt) : m_fmt{fmt} {}

  template <typename... Args>
  std::string format(Args... args) {
    std::ostringstream sbuf;
    // fold expression
    ((sbuf << std::dec) << ... << args);
    return sbuf.str();
  };

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
  logger(level root, std::shared_ptr<sink> sk) : m_root{root}, m_sink{sk} {};

  template <typename... Args>
  void log(const level& lvl, std::string fmt, Args... args) {
    // TODO consume when lvl >= root
    m_sink->consume(record{lvl, formatter{fmt}, std::forward<Args>(args)...});
  };

 private:
  level m_root;
  std::shared_ptr<sink> m_sink;
};

class record {
 public:
  template <typename... Args>
  record(logger::level lvl, formatter&& fmt, Args&&... args) : m_lvl{lvl} {
    m_message = fmt.format(std::forward<Args>(args)...);
  }

  const logger::level& lvl() const { return m_lvl; }

  const std::string& message() const { return m_message; }

 private:
  logger::level m_lvl;
  std::string m_message;
};

}  // namespace kopinions
