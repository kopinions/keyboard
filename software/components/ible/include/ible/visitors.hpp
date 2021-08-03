#pragma once
#include <utility>

#include "ible/specification.hpp"
#include "ible/visitor.hpp"
namespace bt {

class attribute_visitor : public visitor_t<profile_t, service_t, characteristic_t, attribute_t> {
 public:
  friend class update_handles_visitor;
  explicit attribute_visitor(std::shared_ptr<gatt_if_t> gatt_if);

  void visit(profile_t* t) override;

  void visit(service_t* service) override;

  void visit(characteristic_t* t) override;

  void visit(attribute_t* t) override;

  ~attribute_visitor() override = default;

 private:
  std::vector<esp_gatts_attr_db_t> m_attributes;
  std::shared_ptr<gatt_if_t> m_gatt_if;
};

#include <esp_gatts_api.h>

class update_handles_visitor : public visitor_t<profile_t, service_t, characteristic_t, attribute_t> {
 public:
  explicit update_handles_visitor(bt::application_t* application, kopinions::logging::logger* logger,
                                  std::shared_ptr<gatt_if_t> gatt_if, uint16_t uuid, uint16_t num_handles,
                                  uint16_t* handles);

  void visit(profile_t* profile) override;

  void visit(service_t* service) override;

  void visit(characteristic_t* t) override;

  void visit(attribute_t* t) override;

  ~update_handles_visitor() override = default;

 private:
  bt::application_t* m_application;
  kopinions::logging::logger* m_logger;
  std::shared_ptr<gatt_if_t> m_gatt_if;
  bt::uuid_t m_uuid;
  uint16_t m_num_handles;
  uint16_t* m_handles;
  uint16_t m_handle_index{0};
};
class ble_selector_t;

template <typename T>
class selector_t : public visitor_t<bt::profile_t, bt::service_t, bt::characteristic_t, bt::attribute_t> {
 public:
  using base_type = T;
  explicit selector_t(bt::ble_selector_t*);
  static selector_t<T>* $(bt::ble_selector_t*);
  void visit(bt::profile_t* t) override;
  void visit(bt::service_t* t) override;
  void visit(bt::attribute_t* t) override;
  void visit(bt::characteristic_t* t) override;

  T selected();

 private:
  bt::ble_selector_t* m_selector;
  std::vector<bt::characteristic_t*> m_characteristics;
};

class ble_selector_t {
 public:
  static ble_selector_t* profile(bt::profile_t::id_t);
  ble_selector_t* service(bt::service_t::id_t);
  ble_selector_t* characteristic(bt::characteristic_t::id_t);
  ble_selector_t* nth(uint32_t);

 public:
  bt::profile_t::id_t m_pid;
  bt::service_t::id_t m_sid;
  bt::characteristic_t::id_t m_cid;
  uint32_t m_nth;
};

template <typename T>
selector_t<T>* selector_t<T>::$(bt::ble_selector_t* se) {
  return new selector_t<T>{se};
}

template <typename T>
void selector_t<T>::visit(bt::profile_t* t) {
  if (t->id() == m_selector->m_pid) {
    for (auto* service : t->services()) {
      service->accept(this);
    }
  }
}

template <typename T>
void selector_t<T>::visit(bt::service_t* t) {
  if (t->id() == m_selector->m_sid) {
    for (auto* characteristic : t->characteristics()) {
      characteristic->accept(this);
    }
  }
}

template <typename T>
void selector_t<T>::visit(bt::attribute_t* t) {}

template <typename T>
void selector_t<T>::visit(bt::characteristic_t* t) {
  if (t->id() == m_selector->m_cid) {
    m_characteristics.template emplace_back(t);
  }
}

template <typename T>
T selector_t<T>::selected() {
  return m_characteristics[m_selector->m_nth];
}
template <typename T>
selector_t<T>::selector_t(bt::ble_selector_t* selector) : m_selector(selector) {}

}  // namespace bt
