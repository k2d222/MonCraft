#pragma once

#include <memory>
#include <string>
#include <stddef.h>

#include "ui/Component.hpp"
#include "ui/Text.hpp"

class ComboBox : public ui::Component {

protected:
  ComboBox(std::vector<std::string> options, size_t selected);

public:
  static std::unique_ptr<ComboBox> create(std::vector<std::string> options, size_t selected);

  void select(size_t index);
  void select(std::string const& option);

private:
  std::vector<std::string> options;
  size_t selected;
  std::unique_ptr<ui::Text> text;
};
