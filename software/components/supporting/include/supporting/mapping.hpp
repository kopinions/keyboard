#pragma once
#include <boost/di.hpp>
#include <map>

#include "keyboard/key.hpp"
#include "vif/pin.hpp"
using namespace kopinions;

static const std::map<std::pair<pin::id, pin::id>, key_t::id_t> layout_mapping{
    // first row
    {{pin::id::IO26, pin::id::IO2}, key_t::id_t::ESC},
    {{pin::id::IO26, pin::id::IO4}, key_t::id_t::F1},
    {{pin::id::IO26, pin::id::IO5}, key_t::id_t::F2},
    {{pin::id::IO26, pin::id::IO12}, key_t::id_t::F3},
    {{pin::id::IO26, pin::id::IO13}, key_t::id_t::F4},
    {{pin::id::IO26, pin::id::IO14}, key_t::id_t::F5},
    {{pin::id::IO26, pin::id::IO15}, key_t::id_t::F6},
    {{pin::id::IO26, pin::id::IO16}, key_t::id_t::F7},
    {{pin::id::IO26, pin::id::IO17}, key_t::id_t::F8},
    {{pin::id::IO26, pin::id::IO18}, key_t::id_t::F9},
    {{pin::id::IO26, pin::id::IO19}, key_t::id_t::F10},
    {{pin::id::IO26, pin::id::IO21}, key_t::id_t::F11},
    {{pin::id::IO26, pin::id::IO22}, key_t::id_t::F12},
    {{pin::id::IO26, pin::id::IO23}, key_t::id_t::PRINTSCREEN},
    {{pin::id::IO26, pin::id::IO25}, key_t::id_t::SCROLL_LOCK},

    // second row
    {{pin::id::IO27, pin::id::IO2}, key_t::id_t::TILDE},
    {{pin::id::IO27, pin::id::IO4}, key_t::id_t::K1},
    {{pin::id::IO27, pin::id::IO5}, key_t::id_t::K2},
    {{pin::id::IO27, pin::id::IO12}, key_t::id_t::K3},
    {{pin::id::IO27, pin::id::IO13}, key_t::id_t::K4},
    {{pin::id::IO27, pin::id::IO14}, key_t::id_t::K5},
    {{pin::id::IO27, pin::id::IO15}, key_t::id_t::K6},
    {{pin::id::IO27, pin::id::IO16}, key_t::id_t::K7},
    {{pin::id::IO27, pin::id::IO17}, key_t::id_t::K8},
    {{pin::id::IO27, pin::id::IO18}, key_t::id_t::K9},
    {{pin::id::IO27, pin::id::IO19}, key_t::id_t::K0},
    {{pin::id::IO27, pin::id::IO21}, key_t::id_t::MINUS},
    {{pin::id::IO27, pin::id::IO22}, key_t::id_t::EQUAL},
    {{pin::id::IO27, pin::id::IO23}, key_t::id_t::BACKSPACE},
    {{pin::id::IO27, pin::id::IO25}, key_t::id_t::DELETE},

    // third row
    {{pin::id::IO32, pin::id::IO2}, key_t::id_t::TAB},
    {{pin::id::IO32, pin::id::IO4}, key_t::id_t::Q},
    {{pin::id::IO32, pin::id::IO5}, key_t::id_t::W},
    {{pin::id::IO32, pin::id::IO12}, key_t::id_t::E},
    {{pin::id::IO32, pin::id::IO13}, key_t::id_t::R},
    {{pin::id::IO32, pin::id::IO14}, key_t::id_t::T},
    {{pin::id::IO32, pin::id::IO15}, key_t::id_t::Y},
    {{pin::id::IO32, pin::id::IO16}, key_t::id_t::U},
    {{pin::id::IO32, pin::id::IO17}, key_t::id_t::I},
    {{pin::id::IO32, pin::id::IO18}, key_t::id_t::O},
    {{pin::id::IO32, pin::id::IO19}, key_t::id_t::P},
    {{pin::id::IO32, pin::id::IO21}, key_t::id_t::LBRACE},
    {{pin::id::IO32, pin::id::IO22}, key_t::id_t::RBRACE},
    {{pin::id::IO32, pin::id::IO23}, key_t::id_t::BACKSLASH},
    {{pin::id::IO32, pin::id::IO25}, key_t::id_t::INSERT},

    // forth row
    {{pin::id::IO33, pin::id::IO2}, key_t::id_t::CAPS_LOCK},
    {{pin::id::IO33, pin::id::IO4}, key_t::id_t::A},
    {{pin::id::IO33, pin::id::IO5}, key_t::id_t::S},
    {{pin::id::IO33, pin::id::IO12}, key_t::id_t::D},
    {{pin::id::IO33, pin::id::IO13}, key_t::id_t::F},
    {{pin::id::IO33, pin::id::IO14}, key_t::id_t::G},
    {{pin::id::IO33, pin::id::IO15}, key_t::id_t::H},
    {{pin::id::IO33, pin::id::IO16}, key_t::id_t::J},
    {{pin::id::IO33, pin::id::IO17}, key_t::id_t::K},
    {{pin::id::IO33, pin::id::IO18}, key_t::id_t::L},
    {{pin::id::IO33, pin::id::IO19}, key_t::id_t::SEMICOLON},
    {{pin::id::IO33, pin::id::IO21}, key_t::id_t::QUOTE},
    {{pin::id::IO33, pin::id::IO22}, key_t::id_t::ENTER},
    {{pin::id::IO33, pin::id::IO23}, key_t::id_t::PAGE_UP},
    {{pin::id::IO33, pin::id::IO25}, key_t::id_t::PAUSE_BREAK},

    // fifth row
    {{pin::id::IO34, pin::id::IO2}, key_t::id_t::LSHIFT},
    {{pin::id::IO34, pin::id::IO4}, key_t::id_t::Z},
    {{pin::id::IO34, pin::id::IO5}, key_t::id_t::X},
    {{pin::id::IO34, pin::id::IO12}, key_t::id_t::C},
    {{pin::id::IO34, pin::id::IO13}, key_t::id_t::V},
    {{pin::id::IO34, pin::id::IO14}, key_t::id_t::B},
    {{pin::id::IO34, pin::id::IO15}, key_t::id_t::N},
    {{pin::id::IO34, pin::id::IO16}, key_t::id_t::M},
    {{pin::id::IO34, pin::id::IO17}, key_t::id_t::COMMA},
    {{pin::id::IO34, pin::id::IO18}, key_t::id_t::PERIOD},
    {{pin::id::IO34, pin::id::IO19}, key_t::id_t::SLASH},
    {{pin::id::IO34, pin::id::IO21}, key_t::id_t::RSHIFT},
    {{pin::id::IO34, pin::id::IO22}, key_t::id_t::UP},
    {{pin::id::IO34, pin::id::IO23}, key_t::id_t::PAGE_DOWN},
    {{pin::id::IO34, pin::id::IO25}, key_t::id_t::NONE},

    // sixth row
    {{pin::id::IO35, pin::id::IO2}, key_t::id_t::FN},
    {{pin::id::IO35, pin::id::IO4}, key_t::id_t::LCTRL},
    {{pin::id::IO35, pin::id::IO5}, key_t::id_t::LGUI},
    {{pin::id::IO35, pin::id::IO12}, key_t::id_t::LALT},
    {{pin::id::IO35, pin::id::IO13}, key_t::id_t::SPACE},
    {{pin::id::IO35, pin::id::IO14}, key_t::id_t::HOME},
    {{pin::id::IO35, pin::id::IO15}, key_t::id_t::END},
    {{pin::id::IO35, pin::id::IO16}, key_t::id_t::LEFT},
    {{pin::id::IO35, pin::id::IO17}, key_t::id_t::DOWN},
    {{pin::id::IO35, pin::id::IO18}, key_t::id_t::RIGHT},
};

namespace di = boost::di;
constexpr auto mapping = [] {
  return di::make_injector(di::bind<std::map<std::pair<pin::id, pin::id>, key_t::id_t>>.to(layout_mapping));
};
