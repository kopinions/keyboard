#include "ible/builders.hpp"

bt::application_builder_t* bt::application_builder_t::name(const std::string& name) {
  return new bt::application_builder_t(name);
}
bt::application_builder_t* bt::application_builder_t::profile(bt::consumer_t<profile_builder_t> consumer) {
  m_profile_consumers.push_back(consumer);
  return this;
}
bt::application_t* bt::application_builder_t::build() {
  std::vector<bt::profile_t*> profiles;
  for (const auto& consumer : m_profile_consumers) {
    auto b = new profile_builder_t();
    consumer(b);
    profiles.push_back(b->build());
    delete b;
  }
  auto application = new application_t{m_id, profiles};
  return application;
}

bt::application_builder_t* bt::application_builder_t::id(bt::application_t::id_t id) {
  m_id = id;
  return this;
}

bt::application_builder_t::application_builder_t(std::string app_name) : m_app_name(std::move(app_name)) {}

bt::profile_t* bt::profile_builder_t::build() {
  std::vector<bt::service_t*> services;
  for (const auto& consumer : m_services_consumer) {
    auto b = new service_builder_t(&services);
    consumer(b);
    services.emplace_back(b->build());
    delete b;
  }
  return new profile_t(1, services);
}

bt::profile_builder_t* bt::profile_builder_t::service(bt::consumer_t<bt::service_builder_t> consumer) {
  m_services_consumer.emplace_back(consumer);
  return this;
}

bt::service_t* bt::service_builder_t::build() {
  std::vector<characteristic_t*> characteristics;

  for (const auto& consumer : m_characteristic_consumers) {
    auto b = new characteristic_builder_t();
    consumer(b);
    characteristics.push_back(b->build());
    delete b;
  }
  bt::service_t* m_included;

  if (m_service_include_consumer != nullptr) {
    auto b = new service_include_builder_t(m_services);
    m_service_include_consumer(b);
    m_included = b->build();
    delete b;
    return new service_t(m_id, characteristics, m_included);
  }

  return new service_t(m_id, characteristics, nullptr);
}

bt::service_builder_t* bt::service_builder_t::id(bt::service_t::id_t id) {
  m_id = id;
  return this;
}
bt::service_builder_t* bt::service_builder_t::characteristic(bt::consumer_t<bt::characteristic_builder_t> consumer) {
  m_characteristic_consumers.push_back(consumer);
  return this;
}

bt::service_builder_t* bt::service_builder_t::include(bt::consumer_t<bt::service_include_builder_t> consumer) {
  m_service_include_consumer = std::move(consumer);
  return this;
}
bt::service_builder_t::service_builder_t(std::vector<bt::service_t*>* services) : m_services{services} {}

bt::characteristic_t* bt::characteristic_builder_t::build() {
  std::vector<attribute_t*> attributes;

  auto db = new characteristic_declare_builder_t();
  m_declare_builder(db);
  attributes.emplace_back(db->build());
  delete db;

  auto vb = new characteristic_value_builder_t(m_id);
  m_value_builder(vb);
  attributes.emplace_back(vb->build());
  delete vb;

  for (const auto& desc : m_descriptor_builders) {
    auto b = new characteristic_descriptor_builder_t();
    desc(b);
    attributes.emplace_back(b->build());
    delete b;
  }

  return new bt::characteristic_t(m_id, attributes);
}

bt::characteristic_builder_t* bt::characteristic_builder_t::declare(
    consumer_t<characteristic_declare_builder_t> consumer) {
  m_declare_builder = std::move(consumer);
  return this;
}
bt::characteristic_builder_t* bt::characteristic_builder_t::value(
    bt::consumer_t<bt::characteristic_value_builder_t> consumer) {
  m_value_builder = std::move(consumer);
  return this;
}
bt::characteristic_builder_t* bt::characteristic_builder_t::descriptor(
    bt::consumer_t<bt::characteristic_descriptor_builder_t> consumer) {
  m_descriptor_builders.emplace_back(consumer);
  return this;
}
bt::characteristic_builder_t* bt::characteristic_builder_t::id(bt::characteristic_t::id_t id) {
  m_id = id;
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
  return new bt::attribute_t(m_id, m_permission, m_data, m_length, m_max_length, m_automated);
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

bt::service_include_builder_t* bt::service_include_builder_t::id(bt::service_t::id_t id) {
  m_id = id;
  return this;
}

bt::attribute_t* bt::characteristic_value_builder_t::build() {
  return new bt::attribute_t(m_id, m_permission, m_data, m_length, m_max_length);
}
bt::characteristic_value_builder_t::characteristic_value_builder_t(bt::characteristic_t::id_t id) : m_id(id) {}

bt::service_t* bt::service_include_builder_t::build() {
  for (auto& service : *m_services) {
    if (service->id() == m_id) {
      return service;
    }
  }
  return nullptr;
}
bt::service_include_builder_t::service_include_builder_t(std::vector<bt::service_t*>* services)
    : m_services{services} {}
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
  return new bt::attribute_t(bt::characteristic_t::CHARACTERISTIC_DECLARE, m_permission, m_property);
}
bt::characteristic_declare_builder_t::characteristic_declare_builder_t()
    : m_property{characteristic_t::property_t::BROADCAST}, m_permission(characteristic_t::permission_t::READ) {}
