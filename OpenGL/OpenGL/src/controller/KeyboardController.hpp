#pragma once

#include "../entity/Entity.hpp"

#include <glm/glm.hpp>

class KeyboardController {
public:
	KeyboardController();

  void pressedForward();
  void releasedForward();
  void pressedBackward();
  void releasedBackward();
  void pressedLeft();
  void releasedLeft();
  void pressedRight();
  void releasedRight();
  void pressedUp();
  void releasedUp();
  void pressedDown();
  void releasedDown();
  void pressedF5();

  void apply(Entity& character);

private:
  float speed;
  glm::vec3 direction;
  View view;
};