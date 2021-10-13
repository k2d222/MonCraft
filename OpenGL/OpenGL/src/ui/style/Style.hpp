#pragma once

#include "Property.hpp"
#include "Value.hpp"
#include "Specification.hpp"
#include "Type.hpp"

#include <memory>
#include <unordered_set>

namespace ui {

class Component;
class Style;

using style_t = std::shared_ptr<Style>;
using style_const_t = std::shared_ptr<const Style>;

class Style {

public:
  Style();
  Style(std::shared_ptr<const Style> parent);
  Style(std::initializer_list<prop_t> list, style_const_t parent);

  void setParent(style_const_t parent);

  void set(prop_t prop);
  prop_t get(spec_t spec) const;
  bool has(spec_t spec) const;

  // edge case
  static style_t make_style(style_const_t parent);

  // recursive case
  template<typename T, typename... Args>
  static style_t make_style(style_const_t parent, spec_t spec, T val, Args... args) {
    style_t style = make_style(parent, args...);
    style->set(make_property(spec, val));
    return style;
  }

private:
  using propStore_t = std::unordered_map<spec_t, prop_t>;

  propStore_t props;
  style_const_t parent;
};


}; // namespace ui
