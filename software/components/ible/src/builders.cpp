#include "ible/builders.hpp"

#include <ible/specification.hpp>

bt::application_builder_t* bt::application_builder_t::name(const std::string& name) {
  return new bt::application_builder_t(name);
}
bt::application_builder_t* bt::application_builder_t::profile(bt::consumer_t<profile_builder_t> consumer) {
  auto b = new profile_builder_t();
  consumer(b);
  m_profiles.push_back(b->build());
  delete b;
  return this;
}
bt::application_t* bt::application_builder_t::build() {
  auto application = new application_t{m_id};
  for (const auto& p : m_profiles) {
    application->enroll(p);
  }
  return application;
}

bt::application_builder_t* bt::application_builder_t::id(bt::application_t::id_t id) {
  m_id = id;
  return this;
}

bt::application_builder_t::application_builder_t(std::string app_name) : m_app_name(std::move(app_name)) {}

bt::profile_t* bt::profile_builder_t::build() {
  auto profile = new profile_t(1);
  for (const auto& srv : m_services) {
    profile->enroll(srv);
  }

  return profile;
}

bt::profile_builder_t* bt::profile_builder_t::service(bt::consumer_t<bt::service_builder_t> consumer) {
  auto b = new service_builder_t();
  consumer(b);
  m_services.push_back(b->build());
  delete b;
  return this;
}

bt::service_t* bt::service_builder_t::build() { return new service_t(m_id, m_characteristics); }

bt::service_builder_t* bt::service_builder_t::id(bt::service_t::id_t id) {
  m_id = id;
  return this;
}
bt::service_builder_t* bt::service_builder_t::characteristic(bt::consumer_t<bt::characteristic_builder_t> consumer) {
  auto b = new characteristic_builder_t();
  consumer(b);
  m_characteristics.push_back(b->build());
  delete b;
  return this;
}

bt::characteristic_t* bt::characteristic_builder_t::build() {
  std::vector<attribute_t*> attributes;
  attributes.emplace_back(m_declare);
  attributes.emplace_back(m_value);
  attributes.insert(attributes.end(), m_descriptors.begin(), m_descriptors.end());

  return new bt::characteristic_t(attributes);
}

bt::characteristic_builder_t* bt::characteristic_builder_t::declare(
    consumer_t<characteristic_declare_builder_t> consumer) {
  auto b = new characteristic_declare_builder_t();
  consumer(b);
  m_declare = b->build();
  delete b;
  return this;
}
bt::characteristic_builder_t* bt::characteristic_builder_t::value(
    bt::consumer_t<bt::characteristic_value_builder_t> consumer) {
  auto b = new characteristic_value_builder_t();
  consumer(b);
  m_value = b->build();
  delete b;
  return this;
}
bt::characteristic_builder_t* bt::characteristic_builder_t::descriptor(
    bt::consumer_t<bt::characteristic_descriptor_builder_t> consumer) {
  auto b = new characteristic_descriptor_builder_t();
  consumer(b);
  m_descriptors.emplace_back(b->build());
  delete b;
  return this;
}

bt::characteristic_descriptor_builder_t* bt::characteristic_descriptor_builder_t::id(bt::characteristic_t::id_t id) {
  m_id = id;
  return this;
}
bt::characteristic_descriptor_builder_t* bt::characteristic_descriptor_builder_t::permission(
    bt::characteristic_t::permission_t permission) {
  m_permission |= permission;
  return this;
}
bt::characteristic_descriptor_builder_t* bt::characteristic_descriptor_builder_t::value(std::uint8_t* v,
                                                                                        uint16_t length,
                                                                                        uint16_t max_length) {
  m_data = v;
  m_length = length;
  m_max_length = max_length;
  return this;
}
bt::attribute_t* bt::characteristic_descriptor_builder_t::build() {
  return new bt::attribute_t(m_id, characteristic_t::permission_t::WRITE_ENC_MITM, nullptr, 0, 0);
}
bt::characteristic_value_builder_t* bt::characteristic_value_builder_t::id(bt::characteristic_t::id_t id) {
  m_id = id;
  return this;
}
bt::characteristic_value_builder_t* bt::characteristic_value_builder_t::permission(
    bt::characteristic_t::permission_t permission) {
  m_permission |= permission;
  return this;
}
bt::characteristic_value_builder_t* bt::characteristic_value_builder_t::automated(bool automated) {
  m_automated = automated;
  return this;
}
bt::characteristic_value_builder_t* bt::characteristic_value_builder_t::value(std::uint8_t* v, uint16_t length,
                                                                              uint16_t max_length) {
  m_data = v;
  m_length = length;
  m_max_length = max_length;
  return this;
}
bt::attribute_t* bt::characteristic_value_builder_t::build() {
  return new bt::attribute_t(m_id, characteristic_t::permission_t::WRITE_ENC_MITM, nullptr, 0, 0);
}
bt::characteristic_declare_builder_t* bt::characteristic_declare_builder_t::property(
    bt::characteristic_t::property_t property) {
  m_property |= property;
  return this;
}
bt::characteristic_declare_builder_t* bt::characteristic_declare_builder_t::permission(
    bt::characteristic_t::permission_t permission) {
  m_permission |= permission;
  return this;
}
bt::attribute_t* bt::characteristic_declare_builder_t::build() {
  return new bt::attribute_t(bt::characteristic_t::CHARACTERISTIC_DECLARE, m_permission, (uint8_t*)(&m_property),
                             sizeof(m_property), sizeof(m_property));
}
bt::characteristic_declare_builder_t::characteristic_declare_builder_t()
    : m_permission(characteristic_t::permission_t::READ) {}
