#pragma once

#include <memory>
#include <variant>

#include "ible/builder.hpp"
#include "ible/gatt_if.hpp"
#include "ible/repository.hpp"
#include "ible/specification.hpp"
#include "ible/visitor.hpp"
#include "vif.hpp"
namespace bt {

using uuid_t = std::variant<std::uint16_t>;

class attribute_visitor;

enum appearance_t : uint16_t { KEYBOARD = 0x3C1 };

class attribute_visitor;

class characteristic_t : public visitable_t<visitor_t<characteristic_t>> {
 public:
  using id_t = std::uint16_t;

  enum class property_t : uint8_t {
    BROADCAST = (1 << 0),
    READ = (1 << 1),
    WRITE_NR = (1 << 2),
    WRITE = (1 << 3),
    NOTIFY = (1 << 4),
    INDICATE = (1 << 5),
    AUTH = (1 << 6),
    EXT_PROP = (1 << 7),
  };

  enum class permission_t : uint16_t {
    READ = (1 << 0),
    READ_ENCRYPTED = (1 << 1),
    READ_ENC_MITM = (1 << 2),
    WRITE = (1 << 4),
    WRITE_ENCRYPTED = (1 << 5),
    WRITE_ENC_MITM = (1 << 6),
    WRITE_SIGNED = (1 << 7),
    WRITE_SIGNED_MITM = (1 << 8),
  };

  characteristic_t(characteristic_t::id_t, bool, characteristic_t::property_t, characteristic_t::permission_t, uint8_t*,
                   size_t length, size_t max_length);

  friend class attribute_visitor;

 private:
  id_t m_id;
  bool m_automated;
  characteristic_t::property_t m_property;
  characteristic_t::permission_t m_permission;
  std::uint8_t* m_value;
  size_t m_length, m_max_length;

  bool automated();

 public:
  void accept(visitor_t<characteristic_t>* t) override { t->visit(this); }
};

static inline bt::characteristic_t::property_t operator|=(bt::characteristic_t::property_t& l,
                                                          bt::characteristic_t::property_t r) {
  return static_cast<bt::characteristic_t::property_t>(static_cast<uint8_t>(l) | static_cast<uint8_t>(r));
}

static inline bt::characteristic_t::permission_t operator|=(bt::characteristic_t::permission_t& l,
                                                            bt::characteristic_t::permission_t r) {
  return static_cast<bt::characteristic_t::permission_t>(static_cast<uint16_t>(l) | static_cast<uint16_t>(r));
}

class service_t : public visitable_t<visitor_t<service_t>> {
 public:
  using id_t = std::uint16_t;
  explicit service_t(id_t id, std::vector<characteristic_t>);

  std::vector<characteristic_t> characteristics() { return m_characteristics; };

  [[nodiscard]] id_t id() const { return m_id; }

  void accept(visitor_t<service_t>* t) override;

 private:
  esp_gatt_if_t gatt_if;
  id_t m_id;
  std::vector<characteristic_t> m_characteristics;
};

typedef union {
  struct {
    uint16_t notify_enable : 1;
    uint16_t indicate_enable : 1;
    uint16_t reserved : 14;
  };
  uint16_t value;
} ccc_value_t;

class event_t {
 public:
  esp_gatts_cb_event_t event;
  esp_ble_gatts_cb_param_t* param;
};

class profile_t;

class application_t {
 public:
  using id_t = uint16_t;

  virtual id_t id() const { return m_id; }
  virtual id_t id() { return m_id; }
  explicit application_t(id_t id);

  application_t(const application_t&);
  application_t(application_t&&) noexcept;
  virtual ~application_t();

  virtual std::vector<profile_t> profiles() { return {}; }

  virtual void enroll(const profile_t& profile);

  void notified(std::shared_ptr<bt::gatt_if_t>, event_t e);

 private:
  id_t m_id;
  std::shared_ptr<attribute_visitor> m_attributes;
  std::shared_ptr<repository_t<profile_t>> m_profiles;
  kopinions::logging::logger* m_logger;
};

class profile_t : public visitable_t<visitor_t<profile_t>> {
 public:
  using id_t = std::uint16_t;

  explicit profile_t(const id_t& id);

  [[nodiscard]] std::vector<service_t> services() const;

  virtual void enroll(service_t srv);

  void accept(visitor_t<profile_t>* t) override;

  profile_t(const profile_t& o);

  profile_t& operator=(const profile_t&);

  virtual ~profile_t();

  [[nodiscard]] const id_t& id() const;

 private:
  id_t m_id;
  std::map<id_t, service_t> m_services;
};

}  // namespace bt