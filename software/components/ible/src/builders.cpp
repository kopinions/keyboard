#include "ible/builders.hpp"

bt::application_builder_t* bt::application_builder_t::name(const std::string& name) {
  return new bt::application_builder_t(name);
}
bt::application_builder_t* bt::application_builder_t::profile(std::function<void(profile_builder_t*)> consumer) {
  auto b = new profile_builder_t();
  consumer(b);
  m_profiles.push_back(b->build());
  delete b;
  return this;
}
bt::application_t bt::application_builder_t::build() {
  application_t application = application_t{m_id};
  for (auto p : m_profiles) {
    application.enroll(p);
  }
  return application;
}

bt::application_builder_t* bt::application_builder_t::id(bt::application_t::id_t id) {
  m_id = id;
  return this;
}

bt::application_builder_t::application_builder_t(std::string app_name) : m_app_name(std::move(app_name)) {}

bt::profile_t bt::profile_builder_t::build() {
  auto profile = profile_t(1);
  std::cout << m_services.size() << "build size" << std::endl;
  for (const auto& srv : m_services) {
    profile.enroll(srv);
  }

  return profile;
}

bt::profile_builder_t* bt::profile_builder_t::service(std::function<void(bt::service_builder_t*)> consumer) {
  auto b = new service_builder_t();
  consumer(b);
  m_services.push_back(b->build());
  delete b;
  return this;
}

bt::service_t bt::service_builder_t::build() { return service_t(m_id); }

bt::service_builder_t* bt::service_builder_t::id(bt::service_t::id_t id) {
  m_id = id;
  return this;
}
