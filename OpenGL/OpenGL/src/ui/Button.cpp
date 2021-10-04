#include "Button.hpp"

using namespace ui;
using namespace glm;

const spec_t Button::TEXT = MAKE_SPEC("Button::text", std::string);
const spec_t Button::TEXT_COLOR = MAKE_SPEC("Button::textColor", vec4);
const spec_t Button::FONT_SIZE = MAKE_SPEC("Button::fontSize", float);

Button::Button(std::unique_ptr<Component> comp, std::string text, std::shared_ptr<const Font> font)
  : mainComp(std::move(comp)),
    hover(std::make_shared<Style>()),
    pressed(std::make_shared<Style>())
{
  textComp = std::make_unique<Text>(std::move(text), std::move(font));
  mainComp->add(textComp.get());
  add(mainComp.get());

  hover->set(make_property(Text::COLOR, vec4(1.0, 0.0, 0.0, 1.0)));

  pressed->setParent(hover);
  pressed->set(make_property(Text::COLOR, vec4(0.0, 1.0, 0.0, 1.0)));

  textComp->setUseBaseline(false); // TODO: non-heritable styles ?
  mainComp->setPadding(ivec2(10, 5));

  Button::getDefaultStyle()->apply(this);
}

Button::Button(std::string text, std::shared_ptr<const Font> font)
  : Button(std::make_unique<Pane>(), text, font)
{}

void Button::onclick(std::function<void()> callback) {
  this->clickCallback = callback;
}

style_const_t Button::getDefaultStyle() const {
  static style_const_t style = Style::make_style(
    Component::getDefaultStyle(),
    make_property(Text::COLOR, vec4(0.f, 0.f, 0.f, 1.f))
  );

  return style;
}

#include "debug/Debug.hpp"

void Button::onMouseIn(glm::ivec2 pos) {
  hover->apply(this);
}

void Button::onMouseOut(glm::ivec2 pos) {
  if(isPressed()) pressed->revert(this);
  hover->revert(this);
}

bool Button::onMousePressed(glm::ivec2 pos) {
  Component::onMousePressed(pos);
  pressed->apply(this);
  if(clickCallback) clickCallback();
  return true;
}

bool Button::onMouseReleased(glm::ivec2 pos) {
  bool res = Component::onMousePressed(pos);
  pressed->revert(this);
  return res;
}

void Button::setText(std::string text) {
  textComp->setText(std::move(text));
}

std::string Button::getText() const {
  return textComp->getText();
}

void Button::setTextColor(glm::vec4 color) {
  textComp->setColor(color);
}

glm::vec4 Button::getTextColor() const {
  return textComp->getColor();
}

void Button::setFontSize(float fontSize) {
  textComp->setFontSize(fontSize);
}

float Button::getFontSize() const {
  return textComp->getFontSize();
}
