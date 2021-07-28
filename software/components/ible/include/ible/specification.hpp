#pragma once

#include <memory>
#include <variant>

#include "ible/builder.hpp"
#include "ible/dumpable.hpp"
#include "ible/gatt_if.hpp"
#include "ible/repository.hpp"
#include "ible/specification.hpp"
#include "ible/visitor.hpp"
#include "vif.hpp"
namespace bt {

using uint128_t = uint64_t[2];
using uuid_t = std::variant<std::uint16_t, std::uint32_t, bt::uint128_t>;
using handle_t = std::uint16_t;

class attribute_visitor;

enum appearance_t : uint16_t { KEYBOARD = 0x03c0 };

class attribute_visitor;
class attribute_t;

class characteristic_t : public visitable_t<visitor_t<characteristic_t>>, public dumpable_t {
 public:
  static constexpr uint16_t CHARACTERISTIC_DECLARE = ESP_GATT_UUID_CHAR_DECLARE;

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

  struct presentation_format {
    /// Unit (The Unit is a UUID)
    uint16_t unit;
    /// Description
    uint16_t description;
    /// Format
    uint8_t format;
    /// Exponent
    uint8_t exponent;
    /// Name space
    uint8_t name_space;
  };

  explicit characteristic_t(std::vector<bt::attribute_t*>);

  std::vector<bt::attribute_t*> attributes() { return m_attributes; };
  void dump(std::ostream& o) const override;
  friend class attribute_visitor;

 private:
  std::vector<bt::attribute_t*> m_attributes;

 public:
  void accept(visitor_t<characteristic_t>* t) override;
};

class attribute_t : public dumpable_t, public visitable_t<visitor_t<attribute_t>> {
 public:
  friend class attribute_visitor;
  attribute_t(uint16_t, bt::characteristic_t::permission_t, uint8_t*, uint16_t length, uint16_t maxlength,
              bool automated = true);
  attribute_t(const attribute_t&) = delete;
  attribute_t(attribute_t&&) = delete;
  attribute_t& operator=(const attribute_t&) = delete;
  attribute_t& operator=(attribute_t&&) = delete;

  uint16_t id();

  void dump(std::ostream& o) const override;

  void accept(visitor_t<attribute_t>* t) override;

  void handled_by(uint16_t);

 private:
  uint16_t m_uuid;
  bt::characteristic_t::permission_t m_permission;
  std::uint8_t* m_value;
  std::uint16_t m_length;
  std::uint16_t m_max_length;
  bool m_automated;
  handle_t m_handle;
};

inline std::ostream& operator<<(std::ostream& os, const characteristic_t::property_t obj) {
  os << static_cast<uint32_t>(obj);
  return os;
}
inline std::ostream& operator<<(std::ostream& os, const characteristic_t::permission_t obj) {
  os << static_cast<uint32_t>(obj);
  return os;
}

static inline bt::characteristic_t::property_t operator|=(bt::characteristic_t::property_t& l,
                                                          bt::characteristic_t::property_t r) {
  return static_cast<bt::characteristic_t::property_t>(static_cast<uint8_t>(l) | static_cast<uint8_t>(r));
}

static inline bt::characteristic_t::permission_t operator|=(bt::characteristic_t::permission_t& l,
                                                            bt::characteristic_t::permission_t r) {
  return static_cast<bt::characteristic_t::permission_t>(static_cast<uint16_t>(l) | static_cast<uint16_t>(r));
}

static inline bt::characteristic_t::property_t operator|(bt::characteristic_t::property_t l,
                                                         bt::characteristic_t::property_t r) {
  return static_cast<bt::characteristic_t::property_t>(static_cast<uint8_t>(l) | static_cast<uint8_t>(r));
}

static inline bt::characteristic_t::permission_t operator|(bt::characteristic_t::permission_t l,
                                                           bt::characteristic_t::permission_t r) {
  return static_cast<bt::characteristic_t::permission_t>(static_cast<uint16_t>(l) | static_cast<uint16_t>(r));
}

class service_t : public visitable_t<visitor_t<service_t>>, public dumpable_t {
 public:
  friend class attribute_visitor;
  friend class update_handles_visitor;

  using id_t = enum : uint16_t {
    HID = 0x1812,
    BATTERY = 0x180f,
  };

  service_t(id_t id, std::vector<characteristic_t*>, service_t*);

  std::vector<characteristic_t*> characteristics();

  void dump(std::ostream& o) const override;

  id_t& id();

  void handled_by(uint16_t, uint16_t);

  void accept(visitor_t<service_t>* t) override;

 private:
  esp_gatt_if_t gatt_if;
  id_t m_id;
  uint16_t m_handle;
  uint16_t m_end;
  std::vector<characteristic_t*> m_characteristics;
  service_t* m_included;
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

class application_t : public dumpable_t {
 public:
  using id_t = uint16_t;

  virtual id_t id() const { return m_id; }
  virtual id_t id() { return m_id; }
  explicit application_t(id_t id);

  application_t(const application_t&) = delete;
  application_t(application_t&&) = delete;
  application_t& operator=(application_t&) = delete;
  application_t& operator=(application_t&&) = delete;
  virtual ~application_t();

  virtual std::vector<profile_t> profiles() { return {}; }

  virtual void enroll(profile_t* profile);

  void notified(std::shared_ptr<bt::gatt_if_t>, event_t e);
  void dump(std::ostream& o) const override;

 private:
  id_t m_id;
  std::shared_ptr<repository_t<profile_t>> m_profiles;
  kopinions::logging::logger* m_logger;
};

class profile_t : public visitable_t<visitor_t<profile_t>>, public dumpable_t {
 public:
  using id_t = std::uint16_t;

  explicit profile_t(const id_t& id, std::vector<service_t*> services);

  [[nodiscard]] std::vector<service_t*> services() const;

  void accept(visitor_t<profile_t>* t) override;

  profile_t(const profile_t& o) = delete;
  profile_t& operator=(const profile_t&) = delete;

  virtual ~profile_t();

  [[nodiscard]] const id_t& id() const;
  void dump(std::ostream& o) const override;

 private:
  id_t m_id;
  std::vector<service_t*> m_services;
};

}  // namespace bt