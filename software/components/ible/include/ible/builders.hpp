#pragma once
#include <functional>

#include "ible/builders.hpp"
#include "ible/specification.hpp"
#include "specification.hpp"
namespace bt {
class application_builder_t;
class profile_builder_t;
class service_builder_t;
class characteristic_builder_t;

template <typename T>
using consumer_t = std::function<void(T*)>;

class application_builder_t : public ibuilder<bt::application_t*> {
 public:
  explicit application_builder_t(std::string app_name);

  static application_builder_t* name(const std::string& name);

  application_builder_t* id(bt::application_t::id_t id);

  application_builder_t* profile(consumer_t<profile_builder_t> consumer);

  application_t* build() override;

 private:
  std::string m_app_name;

  std::vector<consumer_t<profile_builder_t>> m_profile_consumers;
  bt::application_t::id_t m_id{};
};

class profile_builder_t : public ibuilder<bt::profile_t*> {
 public:
  friend application_builder_t;
  profile_builder_t* service(consumer_t<service_builder_t> consumer);

 private:
  bt::profile_t* build() override;
  std::vector<consumer_t<service_builder_t>> m_services_consumer;
  std::vector<bt::service_t*> m_services;
};

class service_include_builder_t : public ibuilder<bt::service_t*> {
 public:
  friend characteristic_builder_t;
  explicit service_include_builder_t(std::vector<bt::service_t*>* services);
  service_include_builder_t* id(bt::characteristic_t::id_t id);

  service_include_builder_t* permission(bt::characteristic_t::permission_t permission);

  service_include_builder_t* automated(bool automated);

  service_include_builder_t* value(std::uint8_t* v, uint16_t length, uint16_t max_length);

 private:
 public:
  bt::service_t* build() override;

 private:
  bt::characteristic_t::id_t m_id;
  bt::characteristic_t::permission_t m_permission;
  bt::characteristic_t::property_t m_property;
  std::uint8_t* m_data;
  uint16_t m_length, m_max_length;
  bool m_automated{true};
  std::vector<service_t*>* m_services;
};

class service_builder_t : public ibuilder<bt::service_t*> {
 public:
  friend profile_builder_t;

  explicit service_builder_t(std::vector<bt::service_t*>* services);
  service_builder_t* id(bt::service_t::id_t id);

  service_builder_t* include(consumer_t<service_include_builder_t> consumer);

  service_builder_t* characteristic(consumer_t<characteristic_builder_t> consumer);

 private:
  service_t* build() override;

 private:
  bt::service_t::id_t m_id;
  std::vector<consumer_t<bt::characteristic_builder_t>> m_characteristic_consumers;
  consumer_t<bt::service_include_builder_t> m_service_include_consumer;
  std::vector<bt::service_t*>* m_services;
};

class characteristic_declare_builder_t : public ibuilder<bt::attribute_t*> {
 public:
  friend characteristic_builder_t;
  characteristic_declare_builder_t();

  ~characteristic_declare_builder_t() override = default;

  characteristic_declare_builder_t* property(bt::characteristic_t::property_t property);

  characteristic_declare_builder_t* permission(bt::characteristic_t::permission_t permission);

 private:
  bt::attribute_t* build() override;

 private:
  bt::characteristic_t::permission_t m_permission{};
  bt::characteristic_t::property_t m_property;
};

class characteristic_value_builder_t : public ibuilder<bt::attribute_t*> {
 public:
  friend characteristic_builder_t;

  characteristic_value_builder_t* id(bt::characteristic_t::id_t id);

  characteristic_value_builder_t* permission(bt::characteristic_t::permission_t permission);

  characteristic_value_builder_t* automated(bool automated);

  characteristic_value_builder_t* value(std::uint8_t* v, uint16_t length, uint16_t max_length);

 private:
 public:
  bt::attribute_t* build() override;

 private:
  bt::characteristic_t::id_t m_id;
  bt::characteristic_t::permission_t m_permission;
  bt::characteristic_t::property_t m_property;
  std::uint8_t* m_data;
  uint16_t m_length, m_max_length;
  bool m_automated{true};
};

class characteristic_descriptor_builder_t : public ibuilder<bt::attribute_t*> {
 public:
  friend characteristic_builder_t;

  characteristic_descriptor_builder_t* id(bt::characteristic_t::id_t id);

  characteristic_descriptor_builder_t* permission(bt::characteristic_t::permission_t permission);

  characteristic_descriptor_builder_t* value(std::uint8_t* v, uint16_t length, uint16_t max_length);

 public:
  attribute_t* build() override;

 private:
  bt::characteristic_t::id_t m_id;
  bt::characteristic_t::permission_t m_permission;
  std::uint8_t* m_data;
  uint16_t m_length, m_max_length;
  bool m_automated{true};
};

class characteristic_builder_t : public ibuilder<bt::characteristic_t*> {
 public:
  friend service_builder_t;
  characteristic_builder_t* declare(consumer_t<characteristic_declare_builder_t>);
  characteristic_builder_t* value(consumer_t<characteristic_value_builder_t>);
  characteristic_builder_t* descriptor(consumer_t<characteristic_descriptor_builder_t>);

 private:
  characteristic_t* build() override;
  attribute_t* m_declare;
  attribute_t* m_value;
  std::vector<attribute_t*> m_descriptors;
};
}  // namespace bt