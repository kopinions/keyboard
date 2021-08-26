#pragma once
#include <boost/di.hpp>
#include <map>

#include "keyboard/key.hpp"
#include "vif/pin.hpp"
using namespace kopinions;

static const std::map<std::pair<pin::id_t, pin::id_t>, kopinions::key_t::id_t> layout_mapping{
    // first row
    {{pin::id_t::IO26, pin::id_t::IO2}, kopinions::key_t::id_t::ESC},
    {{pin::id_t::IO26, pin::id_t::IO4}, kopinions::key_t::id_t::F1},
    {{pin::id_t::IO26, pin::id_t::IO5}, kopinions::key_t::id_t::F2},
    {{pin::id_t::IO26, pin::id_t::IO12}, kopinions::key_t::id_t::F3},
    {{pin::id_t::IO26, pin::id_t::IO13}, kopinions::key_t::id_t::F4},
    {{pin::id_t::IO26, pin::id_t::IO14}, kopinions::key_t::id_t::F5},
    {{pin::id_t::IO26, pin::id_t::IO15}, kopinions::key_t::id_t::F6},
    {{pin::id_t::IO26, pin::id_t::IO16}, kopinions::key_t::id_t::F7},
    {{pin::id_t::IO26, pin::id_t::IO17}, kopinions::key_t::id_t::F8},
    {{pin::id_t::IO26, pin::id_t::IO18}, kopinions::key_t::id_t::F9},
    {{pin::id_t::IO26, pin::id_t::IO19}, kopinions::key_t::id_t::F10},
    {{pin::id_t::IO26, pin::id_t::IO21}, kopinions::key_t::id_t::F11},
    {{pin::id_t::IO26, pin::id_t::IO22}, kopinions::key_t::id_t::F12},
    {{pin::id_t::IO26, pin::id_t::IO23}, kopinions::key_t::id_t::PRINTSCREEN},
    {{pin::id_t::IO26, pin::id_t::IO25}, kopinions::key_t::id_t::SCROLL_LOCK},

    // second row
    {{pin::id_t::IO27, pin::id_t::IO2}, kopinions::key_t::id_t::TILDE},
    {{pin::id_t::IO27, pin::id_t::IO4}, kopinions::key_t::id_t::K1},
    {{pin::id_t::IO27, pin::id_t::IO5}, kopinions::key_t::id_t::K2},
    {{pin::id_t::IO27, pin::id_t::IO12}, kopinions::key_t::id_t::K3},
    {{pin::id_t::IO27, pin::id_t::IO13}, kopinions::key_t::id_t::K4},
    {{pin::id_t::IO27, pin::id_t::IO14}, kopinions::key_t::id_t::K5},
    {{pin::id_t::IO27, pin::id_t::IO15}, kopinions::key_t::id_t::K6},
    {{pin::id_t::IO27, pin::id_t::IO16}, kopinions::key_t::id_t::K7},
    {{pin::id_t::IO27, pin::id_t::IO17}, kopinions::key_t::id_t::K8},
    {{pin::id_t::IO27, pin::id_t::IO18}, kopinions::key_t::id_t::K9},
    {{pin::id_t::IO27, pin::id_t::IO19}, kopinions::key_t::id_t::K0},
    {{pin::id_t::IO27, pin::id_t::IO21}, kopinions::key_t::id_t::MINUS},
    {{pin::id_t::IO27, pin::id_t::IO22}, kopinions::key_t::id_t::EQUAL},
    {{pin::id_t::IO27, pin::id_t::IO23}, kopinions::key_t::id_t::BACKSPACE},
    {{pin::id_t::IO27, pin::id_t::IO25}, kopinions::key_t::id_t::DELETE},

    // third row
    {{pin::id_t::IO32, pin::id_t::IO2}, kopinions::key_t::id_t::TAB},
    {{pin::id_t::IO32, pin::id_t::IO4}, kopinions::key_t::id_t::Q},
    {{pin::id_t::IO32, pin::id_t::IO5}, kopinions::key_t::id_t::W},
    {{pin::id_t::IO32, pin::id_t::IO12}, kopinions::key_t::id_t::E},
    {{pin::id_t::IO32, pin::id_t::IO13}, kopinions::key_t::id_t::R},
    {{pin::id_t::IO32, pin::id_t::IO14}, kopinions::key_t::id_t::T},
    {{pin::id_t::IO32, pin::id_t::IO15}, kopinions::key_t::id_t::Y},
    {{pin::id_t::IO32, pin::id_t::IO16}, kopinions::key_t::id_t::U},
    {{pin::id_t::IO32, pin::id_t::IO17}, kopinions::key_t::id_t::I},
    {{pin::id_t::IO32, pin::id_t::IO18}, kopinions::key_t::id_t::O},
    {{pin::id_t::IO32, pin::id_t::IO19}, kopinions::key_t::id_t::P},
    {{pin::id_t::IO32, pin::id_t::IO21}, kopinions::key_t::id_t::LBRACE},
    {{pin::id_t::IO32, pin::id_t::IO22}, kopinions::key_t::id_t::RBRACE},
    {{pin::id_t::IO32, pin::id_t::IO23}, kopinions::key_t::id_t::BACKSLASH},
    {{pin::id_t::IO32, pin::id_t::IO25}, kopinions::key_t::id_t::INSERT},

    // forth row
    {{pin::id_t::IO33, pin::id_t::IO2}, kopinions::key_t::id_t::CAPS_LOCK},
    {{pin::id_t::IO33, pin::id_t::IO4}, kopinions::key_t::id_t::A},
    {{pin::id_t::IO33, pin::id_t::IO5}, kopinions::key_t::id_t::S},
    {{pin::id_t::IO33, pin::id_t::IO12}, kopinions::key_t::id_t::D},
    {{pin::id_t::IO33, pin::id_t::IO13}, kopinions::key_t::id_t::F},
    {{pin::id_t::IO33, pin::id_t::IO14}, kopinions::key_t::id_t::G},
    {{pin::id_t::IO33, pin::id_t::IO15}, kopinions::key_t::id_t::H},
    {{pin::id_t::IO33, pin::id_t::IO16}, kopinions::key_t::id_t::J},
    {{pin::id_t::IO33, pin::id_t::IO17}, kopinions::key_t::id_t::K},
    {{pin::id_t::IO33, pin::id_t::IO18}, kopinions::key_t::id_t::L},
    {{pin::id_t::IO33, pin::id_t::IO19}, kopinions::key_t::id_t::SEMICOLON},
    {{pin::id_t::IO33, pin::id_t::IO21}, kopinions::key_t::id_t::QUOTE},
    {{pin::id_t::IO33, pin::id_t::IO22}, kopinions::key_t::id_t::ENTER},
    {{pin::id_t::IO33, pin::id_t::IO23}, kopinions::key_t::id_t::PAGE_UP},
    {{pin::id_t::IO33, pin::id_t::IO25}, kopinions::key_t::id_t::PAUSE_BREAK},

    // fifth row
    {{pin::id_t::IO34, pin::id_t::IO2}, kopinions::key_t::id_t::LSHIFT},
    {{pin::id_t::IO34, pin::id_t::IO4}, kopinions::key_t::id_t::Z},
    {{pin::id_t::IO34, pin::id_t::IO5}, kopinions::key_t::id_t::X},
    {{pin::id_t::IO34, pin::id_t::IO12}, kopinions::key_t::id_t::C},
    {{pin::id_t::IO34, pin::id_t::IO13}, kopinions::key_t::id_t::V},
    {{pin::id_t::IO34, pin::id_t::IO14}, kopinions::key_t::id_t::B},
    {{pin::id_t::IO34, pin::id_t::IO15}, kopinions::key_t::id_t::N},
    {{pin::id_t::IO34, pin::id_t::IO16}, kopinions::key_t::id_t::M},
    {{pin::id_t::IO34, pin::id_t::IO17}, kopinions::key_t::id_t::COMMA},
    {{pin::id_t::IO34, pin::id_t::IO18}, kopinions::key_t::id_t::PERIOD},
    {{pin::id_t::IO34, pin::id_t::IO19}, kopinions::key_t::id_t::SLASH},
    {{pin::id_t::IO34, pin::id_t::IO21}, kopinions::key_t::id_t::RSHIFT},
    {{pin::id_t::IO34, pin::id_t::IO22}, kopinions::key_t::id_t::UP},
    {{pin::id_t::IO34, pin::id_t::IO23}, kopinions::key_t::id_t::PAGE_DOWN},
    {{pin::id_t::IO34, pin::id_t::IO25}, kopinions::key_t::id_t::NONE},

    // sixth row
    {{pin::id_t::IO35, pin::id_t::IO2}, kopinions::key_t::id_t::FN},
    {{pin::id_t::IO35, pin::id_t::IO4}, kopinions::key_t::id_t::LCTRL},
    {{pin::id_t::IO35, pin::id_t::IO5}, kopinions::key_t::id_t::LGUI},
    {{pin::id_t::IO35, pin::id_t::IO12}, kopinions::key_t::id_t::LALT},
    {{pin::id_t::IO35, pin::id_t::IO13}, kopinions::key_t::id_t::SPACE},
    {{pin::id_t::IO35, pin::id_t::IO14}, kopinions::key_t::id_t::HOME},
    {{pin::id_t::IO35, pin::id_t::IO15}, kopinions::key_t::id_t::END},
    {{pin::id_t::IO35, pin::id_t::IO16}, kopinions::key_t::id_t::LEFT},
    {{pin::id_t::IO35, pin::id_t::IO17}, kopinions::key_t::id_t::DOWN},
    {{pin::id_t::IO35, pin::id_t::IO18}, kopinions::key_t::id_t::RIGHT},
};

namespace di = boost::di;
constexpr auto mapping = [] {
  return di::make_injector(di::bind<std::map<std::pair<pin::id_t, pin::id_t>, kopinions::key_t::id_t>>.to(layout_mapping));
};
