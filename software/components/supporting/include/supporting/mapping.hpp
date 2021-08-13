#pragma once
#include <boost/di.hpp>
#include <map>

#include "vif/pin.hpp"
#include "keyboard/key.hpp"
using namespace kopinions;

static const std::map<std::pair<pin::id, pin::id>, key::identification> layout_mapping{
    // first row
    {{pin::id::IO26, pin::id::IO2}, key::identification::ESC},
    {{pin::id::IO26, pin::id::IO4}, key::identification::F1},
    {{pin::id::IO26, pin::id::IO5}, key::identification::F2},
    {{pin::id::IO26, pin::id::IO12}, key::identification::F3},
    {{pin::id::IO26, pin::id::IO13}, key::identification::F4},
    {{pin::id::IO26, pin::id::IO14}, key::identification::F5},
    {{pin::id::IO26, pin::id::IO15}, key::identification::F6},
    {{pin::id::IO26, pin::id::IO16}, key::identification::F7},
    {{pin::id::IO26, pin::id::IO17}, key::identification::F8},
    {{pin::id::IO26, pin::id::IO18}, key::identification::F9},
    {{pin::id::IO26, pin::id::IO19}, key::identification::F10},
    {{pin::id::IO26, pin::id::IO21}, key::identification::F11},
    {{pin::id::IO26, pin::id::IO22}, key::identification::F12},
    {{pin::id::IO26, pin::id::IO23}, key::identification::PRINTSCREEN},
    {{pin::id::IO26, pin::id::IO25}, key::identification::SCROLL_LOCK},

    // second row
    {{pin::id::IO27, pin::id::IO2}, key::identification::TILDE},
    {{pin::id::IO27, pin::id::IO4}, key::identification::K1},
    {{pin::id::IO27, pin::id::IO5}, key::identification::K2},
    {{pin::id::IO27, pin::id::IO12}, key::identification::K3},
    {{pin::id::IO27, pin::id::IO13}, key::identification::K4},
    {{pin::id::IO27, pin::id::IO14}, key::identification::K5},
    {{pin::id::IO27, pin::id::IO15}, key::identification::K6},
    {{pin::id::IO27, pin::id::IO16}, key::identification::K7},
    {{pin::id::IO27, pin::id::IO17}, key::identification::K8},
    {{pin::id::IO27, pin::id::IO18}, key::identification::K9},
    {{pin::id::IO27, pin::id::IO19}, key::identification::K0},
    {{pin::id::IO27, pin::id::IO21}, key::identification::MINUS},
    {{pin::id::IO27, pin::id::IO22}, key::identification::EQUAL},
    {{pin::id::IO27, pin::id::IO23}, key::identification::BACKSPACE},
    {{pin::id::IO27, pin::id::IO25}, key::identification::DELETE},

    // third row
    {{pin::id::IO32, pin::id::IO2}, key::identification::TAB},
    {{pin::id::IO32, pin::id::IO4}, key::identification::Q},
    {{pin::id::IO32, pin::id::IO5}, key::identification::W},
    {{pin::id::IO32, pin::id::IO12}, key::identification::E},
    {{pin::id::IO32, pin::id::IO13}, key::identification::R},
    {{pin::id::IO32, pin::id::IO14}, key::identification::T},
    {{pin::id::IO32, pin::id::IO15}, key::identification::Y},
    {{pin::id::IO32, pin::id::IO16}, key::identification::U},
    {{pin::id::IO32, pin::id::IO17}, key::identification::I},
    {{pin::id::IO32, pin::id::IO18}, key::identification::O},
    {{pin::id::IO32, pin::id::IO19}, key::identification::P},
    {{pin::id::IO32, pin::id::IO21}, key::identification::LBRACE},
    {{pin::id::IO32, pin::id::IO22}, key::identification::RBRACE},
    {{pin::id::IO32, pin::id::IO23}, key::identification::BACKSLASH},
    {{pin::id::IO32, pin::id::IO25}, key::identification::INSERT},

    // forth row
    {{pin::id::IO33, pin::id::IO2}, key::identification::CAPS_LOCK},
    {{pin::id::IO33, pin::id::IO4}, key::identification::A},
    {{pin::id::IO33, pin::id::IO5}, key::identification::S},
    {{pin::id::IO33, pin::id::IO12}, key::identification::D},
    {{pin::id::IO33, pin::id::IO13}, key::identification::F},
    {{pin::id::IO33, pin::id::IO14}, key::identification::G},
    {{pin::id::IO33, pin::id::IO15}, key::identification::H},
    {{pin::id::IO33, pin::id::IO16}, key::identification::J},
    {{pin::id::IO33, pin::id::IO17}, key::identification::K},
    {{pin::id::IO33, pin::id::IO18}, key::identification::L},
    {{pin::id::IO33, pin::id::IO19}, key::identification::SEMICOLON},
    {{pin::id::IO33, pin::id::IO21}, key::identification::QUOTE},
    {{pin::id::IO33, pin::id::IO22}, key::identification::ENTER},
    {{pin::id::IO33, pin::id::IO23}, key::identification::PAGE_UP},
    {{pin::id::IO33, pin::id::IO25}, key::identification::PAUSE_BREAK},

    // fifth row
    {{pin::id::IO34, pin::id::IO2}, key::identification::LSHIFT},
    {{pin::id::IO34, pin::id::IO4}, key::identification::Z},
    {{pin::id::IO34, pin::id::IO5}, key::identification::X},
    {{pin::id::IO34, pin::id::IO12}, key::identification::C},
    {{pin::id::IO34, pin::id::IO13}, key::identification::V},
    {{pin::id::IO34, pin::id::IO14}, key::identification::B},
    {{pin::id::IO34, pin::id::IO15}, key::identification::N},
    {{pin::id::IO34, pin::id::IO16}, key::identification::M},
    {{pin::id::IO34, pin::id::IO17}, key::identification::COMMA},
    {{pin::id::IO34, pin::id::IO18}, key::identification::PERIOD},
    {{pin::id::IO34, pin::id::IO19}, key::identification::SLASH},
    {{pin::id::IO34, pin::id::IO21}, key::identification::RSHIFT},
    {{pin::id::IO34, pin::id::IO22}, key::identification::UP},
    {{pin::id::IO34, pin::id::IO23}, key::identification::PAGE_DOWN},
    {{pin::id::IO34, pin::id::IO25}, key::identification::NONE},

    // sixth row
    {{pin::id::IO35, pin::id::IO2}, key::identification::FN},
    {{pin::id::IO35, pin::id::IO4}, key::identification::LCTRL},
    {{pin::id::IO35, pin::id::IO5}, key::identification::LGUI},
    {{pin::id::IO35, pin::id::IO12}, key::identification::LALT},
    {{pin::id::IO35, pin::id::IO13}, key::identification::SPACE},
    {{pin::id::IO35, pin::id::IO14}, key::identification::HOME},
    {{pin::id::IO35, pin::id::IO15}, key::identification::END},
    {{pin::id::IO35, pin::id::IO16}, key::identification::LEFT},
    {{pin::id::IO35, pin::id::IO17}, key::identification::DOWN},
    {{pin::id::IO35, pin::id::IO18}, key::identification::RIGHT},
};

namespace di = boost::di;
constexpr auto mapping = [] {
  return di::make_injector(di::bind<std::map<std::pair<pin::id, pin::id>, key::identification>>.to(layout_mapping));
};
