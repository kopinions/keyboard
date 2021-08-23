#include "link/message.hpp"

kopinions::message_t::message_t(std::unique_ptr<const uint8_t[]> data, unsigned int size)
    : m_data{std::move(data)}, m_size{size} {}

const uint8_t* kopinions::message_t::payload() const { return m_data.get(); }
uint32_t kopinions::message_t::size() const { return m_size; }
