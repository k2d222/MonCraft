#include "Box.hpp"

#include <utility>
#include <glm/glm.hpp>

#include "ui/Component.hpp"
#include "ui/style/Type.hpp"
#include "ui/style/Value.hpp"

using namespace ui;
using namespace glm;

MAKE_TYPE(Box::Orientation);
const spec_t Box::GAP = MAKE_SPEC("Box::gap", int);
const spec_t Box::ORIENTATION = MAKE_SPEC("Box::orientation", Box::Orientation);

Box::Box()
{}

std::unique_ptr<Box> Box::create() {
  auto comp = std::unique_ptr<Box>(new Box());
  comp->initialize();
  return comp;
}

void Box::setProperty(prop_t prop) {
  if(prop.spec == Box::GAP) {
    setGap(prop.value->get<int>());
  }
  if(prop.spec == Box::ORIENTATION) {
    setOrientation(prop.value->get<Box::Orientation>());
  }
  else {
    Component::setProperty(prop);
  }
}

prop_t Box::getProperty(spec_t spec) const {
  if(spec == Box::GAP) {
    return make_prop(spec, getGap());
  }
  else {
    return Component::getProperty(spec);
  }
}

style_const_t Box::getDefaultStyle() const {
  static style_const_t style = Style::make_style(
    Component::getDefaultStyle(),
    Box::GAP, 0,
    Box::ORIENTATION, Orientation::VERTICAL
  );

  return style;
}


void Box::pack(size_t index, Component* comp) {
  auto it = cells.begin() + index;
  it = cells.insert(it, Cell::create(comp));
  add(it->get());
}

void Box::pack_end(Component* comp) {
  cells.emplace_back(Cell::create(comp));
  add(cells.back().get());
}

void Box::pack_start(Component* comp) {
  auto it = cells.emplace(cells.begin(), Cell::create(comp));
  add(it->get());
}

void Box::unpack(Component* comp) {
  for(auto it = cells.cbegin(); it != cells.cend(); ) {
    if((*it)->contains(comp)) it = cells.erase(it);
    else ++it;
  }
}

void Box::unpackAt(size_t index) {
  if(index >= cells.size())
    throw std::out_of_range("index out of range");
  cells.erase(cells.begin() + index);
}

void Box::pack(size_t index, std::unique_ptr<Component> comp) {
  auto it = cells.begin() + index;
  it = cells.insert(it, Cell::create(move(comp)));
  add(it->get());
}

void Box::pack_end(std::unique_ptr<Component> comp) {
  cells.emplace_back(Cell::create(move(comp)));
  add(cells.back().get());
}

void Box::pack_start(std::unique_ptr<Component> comp) {
  auto it = cells.emplace(cells.begin(), Cell::create(move(comp)));
  add(it->get());
}

void Box::draw() {
  updateCells();

  Component::draw();
}

void Box::updateCells() {
  int offset = 0;
  std::vector<int> offsets(cells.size());
  int i = getOrientation() == Orientation::HORIZONTAL ? 0 : 1;
  ivec2 maxSize(0);

  for(auto const& cell : cells) {
    ivec2 pos(0);
    pos[i] = offset;
    cell->setPosition(pos);
    maxSize = max(maxSize, cell->getAbsoluteSize());
    offset += cell->getAbsoluteSize()[i] + getGap();
  }

  maxSize[i] = 0;
  for(auto const& cell : cells) {
    cell->setSize(maxSize);
  }
}

void Box::setGap(int gap) {
  setStyle(GAP, gap);
}

int Box::getGap() const {
  return getStyle<int>(GAP);
}

void Box::setOrientation(Orientation orientation) {
  if(orientation != getOrientation()) {
    setStyle(ORIENTATION, orientation);
    updateCells();
  }
}

Box::Orientation Box::getOrientation() const {
  return getStyle<Orientation>(ORIENTATION);
}

Box::Cell::Cell() {}

std::unique_ptr<Box::Cell> Box::Cell::create(Component* comp) {
  auto cell = std::unique_ptr<Cell>(new Cell());
  cell->add(comp);
  return cell;
}

std::unique_ptr<Box::Cell> Box::Cell::create(std::unique_ptr<Component> comp) {
  auto cell = std::unique_ptr<Cell>(new Cell());
  cell->add(move(comp));
  return cell;
}

bool Box::Cell::contains(Component* comp) const {
  return children.at(0) == comp;
}
