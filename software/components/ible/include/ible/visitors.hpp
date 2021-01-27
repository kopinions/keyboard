#pragma once
#include "ible/specification.hpp"
#include "ible/visitor.hpp"
namespace bt {

class attribute_t {
 public:
  enum class type : uint16_t {
    INCLUDE_DECLARATION = 0x2802,
    CHARACTER_DECLARATION = 0x2803,
  };
};

class attribute_visitor : public visitor_t<profile_t, service_t, characteristic_t> {
 public:
  attribute_visitor(std::shared_ptr<gatt_if_t> gatt_if) { m_gatt_if = gatt_if; }

  void visit(profile_t* t) override;

  void visit(service_t* t) override;

  void visit(characteristic_t* t) override;

  ~attribute_visitor() override = default;

 private:
  std::vector<esp_gatts_attr_db_t> m_attributes;
  std::shared_ptr<gatt_if_t> m_gatt_if;
};
}  // namespace bt
