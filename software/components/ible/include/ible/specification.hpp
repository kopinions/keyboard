#pragma once
#include <esp_gatt_defs.h>
#include <esp_gatts_api.h>

#include <memory>
#include <variant>

#include "ible/builder.hpp"
#include "ible/repository.hpp"
#include "ible/specification.hpp"
#include "ible/visitor.hpp"
#include "vif.hpp"
namespace bt {

class gatt_if_t {
 public:
  virtual esp_err_t create_attr_tab(const esp_gatts_attr_db_t* gatts_attr_db, uint8_t max_nb_attr,
                                    uint8_t srvc_inst_id) = 0;
};

class esp_gatt : public gatt_if_t {
 public:
  explicit esp_gatt(esp_gatt_if_t gatt_if) : m_gatt_if(gatt_if) {}

  esp_err_t create_attr_tab(const esp_gatts_attr_db_t* gatts_attr_db, uint8_t max_nb_attr,
                            uint8_t srvc_inst_id) override {
    return esp_ble_gatts_create_attr_tab(gatts_attr_db, m_gatt_if, max_nb_attr, srvc_inst_id);
  }

 private:
  esp_gatt_if_t m_gatt_if;
};

using uuid_t = std::variant<std::uint16_t>;

class attribute_visitor;

class attribute_t {
 public:
  enum class type : uint16_t {
    INCLUDE_DECLARATION = 0x2802,
    CHARACTER_DECLARATION = 0x2803,
  };
};

class attribute_visitor;

class characteristic_t : public visitable_t<visitor_t<characteristic_t>> {
 public:
  using id_t = std::uint16_t;
  friend class attribute_visitor;

 private:
  uint8_t auto_rsp;
  uint16_t uuid_length;
  uint8_t* uuid_p;
  uint16_t perm;
  uint16_t max_length;
  uint16_t length;
  uint8_t* value;

 public:
  void accept(visitor_t<characteristic_t>* t) override { t->visit(this); }
};

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
  std::shared_ptr<kopinions::logging::logger> m_logger;
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

  esp_gatt_srvc_id_t service_id;
  uint16_t gatts_if;
  uint16_t conn_id;
  uint16_t service_handle;
  esp_bt_uuid_t char_uuid;
  uint16_t char_handle;
  uint16_t descr_handle;
  esp_bt_uuid_t descr_uuid;

  [[nodiscard]] const id_t& id() const;

 private:
  id_t m_id;
  std::map<id_t, service_t> m_services;
};

enum appearance_t : uint16_t { KEYBOARD = 0x3C1 };

class topic {
 public:
  virtual void subscribed() = 0;
};

class subscriber {
 public:
  virtual void subscribe(std::shared_ptr<topic>) = 0;
};

}  // namespace bt