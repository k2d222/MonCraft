#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "ui/Key.hpp"
#include "ui/Component.hpp"
#include "ui/Text.hpp"


class KeySelector : public ui::Component {

protected:
  KeySelector(Key key);
  virtual void onKeyPressed(Key k) override;
  virtual void onMouseIn(glm::ivec2 pos) override;
  virtual void onMouseOut(glm::ivec2 pos) override;
  virtual bool onActivate() override;
  virtual void onDeactivated() override;

public:
  void setKey(Key key);
  Key getKey() const;

  static std::unique_ptr<KeySelector> create(Key key);

private:
  Key key;
  std::unique_ptr<ui::Text> text;
};
