#pragma once
#include "ible/builders.hpp"
#include "ible/specification.hpp"
namespace bt {
class application_builder_t;
class profile_builder_t;
class service_builder_t;
class characteristic_builder_t;

template <typename T>
using consumer_t = std::function<void(T*)>;

class application_builder_t : public ibuilder<bt::application_t> {
 public:
  explicit application_builder_t(std::string app_name);

  static application_builder_t* name(const std::string& name);

  application_builder_t* id(bt::application_t::id_t id);

  application_builder_t* profile(consumer_t<profile_builder_t> consumer);

  application_t build() override;

 private:
  std::string m_app_name;
  std::vector<bt::profile_t> m_profiles;
  bt::application_t::id_t m_id;
};

class profile_builder_t : public ibuilder<bt::profile_t> {
 public:
  friend application_builder_t;
  profile_builder_t* service(std::function<void(service_builder_t*)> consumer);

 private:
  bt::profile_t build() override;
  std::vector<bt::service_t> m_services;
};

class service_builder_t : public ibuilder<bt::service_t> {
 public:
  friend profile_builder_t;

  service_builder_t* id(bt::service_t::id_t id);

  service_builder_t* characteristic(consumer_t<characteristic_builder_t> consumer);

 private:
  service_t build() override;

 private:
  bt::service_t::id_t m_id;
  std::vector<characteristic_t> m_characteristics;
};

class characteristic_builder_t : public ibuilder<bt::characteristic_t> {
 public:
  friend service_builder_t;
  characteristic_builder_t* id(bt::characteristic_t::id_t id);

 private:
  characteristic_t build() override;
  bt::characteristic_t::id_t m_id;
};
}  // namespace bt