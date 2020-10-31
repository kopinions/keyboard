#pragma once
#include <boost/di.hpp>
#include <map>

#include "key.hpp"
#include "pin.hpp"
using namespace kopinions;

std::map<std::pair<pin::id, pin::id>, key::id> mapping{
    // first row
    {{pin::id::IO26, pin::id::IO2}, key::id::ESC},
    {{pin::id::IO26, pin::id::IO4}, key::id::F1},
    {{pin::id::IO26, pin::id::IO5}, key::id::F2},
    {{pin::id::IO26, pin::id::IO12}, key::id::F3},
    {{pin::id::IO26, pin::id::IO13}, key::id::F4},
    {{pin::id::IO26, pin::id::IO14}, key::id::F5},
    {{pin::id::IO26, pin::id::IO15}, key::id::F6},
    {{pin::id::IO26, pin::id::IO16}, key::id::F7},
    {{pin::id::IO26, pin::id::IO17}, key::id::F8},
    {{pin::id::IO26, pin::id::IO18}, key::id::F9},
    {{pin::id::IO26, pin::id::IO19}, key::id::F10},
    {{pin::id::IO26, pin::id::IO21}, key::id::F11},
    {{pin::id::IO26, pin::id::IO22}, key::id::F12},
    {{pin::id::IO26, pin::id::IO23}, key::id::PRINTSCREEN},
    {{pin::id::IO26, pin::id::IO25}, key::id::SCROLL_LOCK},

    // second row
    {{pin::id::IO27, pin::id::IO2}, key::id::TILDE},
    {{pin::id::IO27, pin::id::IO4}, key::id::K1},
    {{pin::id::IO27, pin::id::IO5}, key::id::K2},
    {{pin::id::IO27, pin::id::IO12}, key::id::K3},
    {{pin::id::IO27, pin::id::IO13}, key::id::K4},
    {{pin::id::IO27, pin::id::IO14}, key::id::K5},
    {{pin::id::IO27, pin::id::IO15}, key::id::K6},
    {{pin::id::IO27, pin::id::IO16}, key::id::K7},
    {{pin::id::IO27, pin::id::IO17}, key::id::K8},
    {{pin::id::IO27, pin::id::IO18}, key::id::K9},
    {{pin::id::IO27, pin::id::IO19}, key::id::K0},
    {{pin::id::IO27, pin::id::IO21}, key::id::MINUS},
    {{pin::id::IO27, pin::id::IO22}, key::id::EQUAL},
    {{pin::id::IO27, pin::id::IO23}, key::id::BACKSPACE},
    {{pin::id::IO27, pin::id::IO25}, key::id::DELETE},

    // third row
    {{pin::id::IO32, pin::id::IO2}, key::id::TAB},
    {{pin::id::IO32, pin::id::IO4}, key::id::Q},
    {{pin::id::IO32, pin::id::IO5}, key::id::W},
    {{pin::id::IO32, pin::id::IO12}, key::id::E},
    {{pin::id::IO32, pin::id::IO13}, key::id::R},
    {{pin::id::IO32, pin::id::IO14}, key::id::T},
    {{pin::id::IO32, pin::id::IO15}, key::id::Y},
    {{pin::id::IO32, pin::id::IO16}, key::id::U},
    {{pin::id::IO32, pin::id::IO17}, key::id::I},
    {{pin::id::IO32, pin::id::IO18}, key::id::O},
    {{pin::id::IO32, pin::id::IO19}, key::id::P},
    {{pin::id::IO32, pin::id::IO21}, key::id::LBRACE},
    {{pin::id::IO32, pin::id::IO22}, key::id::RBRACE},
    {{pin::id::IO32, pin::id::IO23}, key::id::BACKSLASH},
    {{pin::id::IO32, pin::id::IO25}, key::id::INSERT},

    // forth row
    {{pin::id::IO33, pin::id::IO2}, key::id::CAPS_LOCK},
    {{pin::id::IO33, pin::id::IO4}, key::id::A},
    {{pin::id::IO33, pin::id::IO5}, key::id::S},
    {{pin::id::IO33, pin::id::IO12}, key::id::D},
    {{pin::id::IO33, pin::id::IO13}, key::id::F},
    {{pin::id::IO33, pin::id::IO14}, key::id::G},
    {{pin::id::IO33, pin::id::IO15}, key::id::H},
    {{pin::id::IO33, pin::id::IO16}, key::id::J},
    {{pin::id::IO33, pin::id::IO17}, key::id::K},
    {{pin::id::IO33, pin::id::IO18}, key::id::L},
    {{pin::id::IO33, pin::id::IO19}, key::id::SEMICOLON},
    {{pin::id::IO33, pin::id::IO21}, key::id::QUOTE},
    {{pin::id::IO33, pin::id::IO22}, key::id::ENTER},
    {{pin::id::IO33, pin::id::IO23}, key::id::PAGE_UP},
    {{pin::id::IO33, pin::id::IO25}, key::id::PAUSE_BREAK},

    // fifth row
    {{pin::id::IO34, pin::id::IO2}, key::id::SHIFT},
    {{pin::id::IO34, pin::id::IO4}, key::id::Z},
    {{pin::id::IO34, pin::id::IO5}, key::id::X},
    {{pin::id::IO34, pin::id::IO12}, key::id::C},
    {{pin::id::IO34, pin::id::IO13}, key::id::V},
    {{pin::id::IO34, pin::id::IO14}, key::id::B},
    {{pin::id::IO34, pin::id::IO15}, key::id::N},
    {{pin::id::IO34, pin::id::IO16}, key::id::M},
    {{pin::id::IO34, pin::id::IO17}, key::id::COMMA},
    {{pin::id::IO34, pin::id::IO18}, key::id::PERIOD},
    {{pin::id::IO34, pin::id::IO19}, key::id::SLASH},
    {{pin::id::IO34, pin::id::IO21}, key::id::RSHIFT},
    {{pin::id::IO34, pin::id::IO22}, key::id::UP},
    {{pin::id::IO34, pin::id::IO23}, key::id::PAGE_DOWN},
    {{pin::id::IO34, pin::id::IO25}, key::id::NONE},

    // sixth row
    {{pin::id::IO35, pin::id::IO2}, key::id::FN},
    {{pin::id::IO35, pin::id::IO4}, key::id::CTRL},
    {{pin::id::IO35, pin::id::IO5}, key::id::GUI},
    {{pin::id::IO35, pin::id::IO12}, key::id::ALT},
    {{pin::id::IO35, pin::id::IO13}, key::id::SPACE},
    {{pin::id::IO35, pin::id::IO14}, key::id::HOME},
    {{pin::id::IO35, pin::id::IO15}, key::id::END},
    {{pin::id::IO35, pin::id::IO16}, key::id::LEFT},
    {{pin::id::IO35, pin::id::IO17}, key::id::DOWN},
    {{pin::id::IO35, pin::id::IO18}, key::id::RIGHT},
};

namespace di = boost::di;
auto layout_mapping = [] { return di::make_injector(di::bind<std::map<std::pair<pin::id, pin::id>, key::id>>.to(mapping)); };
