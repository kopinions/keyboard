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

}  // namespace bt
