#include "Checkbox.hpp"

#include <memory>


#include "ui/Component.hpp"
#include "ui/Button.hpp"
#include "ui/Image.hpp"

using namespace ui;

Checkbox::Checkbox()
  : checked(false), pos(119, 1179)
{
  img = Image::create(pos, {43, 20});
  img->setSize({43, 20});
  auto btn = Button::create();
  btn->onClick([&] { setChecked(!getChecked()); });
  btn->add(img.get());
  add(move(btn));
}

bool Checkbox::getChecked() const {
  return checked;
}

void Checkbox::setChecked(bool checked) {
  this->checked = checked;
  glm::ivec2 off = img->getTextureOffset();
  if(checked) off = pos + glm::vec2(46, 0);
  else off = pos;

  img->setTextureOffset(off);
}

std::unique_ptr<Checkbox> Checkbox::create() {
  auto check = std::unique_ptr<Checkbox>(new Checkbox());
  check->initialize();
  return check;
}
