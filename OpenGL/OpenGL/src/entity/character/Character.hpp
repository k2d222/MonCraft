#pragma once

#include "../Entity.hpp"
#include "../../gl/Loader.hpp"

#include "LeftArm.hpp"
#include "RightArm.hpp"
#include "LeftLeg.hpp"
#include "RightLeg.hpp"
#include "LeftLeg.hpp"
#include "RightLeg.hpp"
#include "Head.hpp"
#include "Chest.hpp"

class Character : public Entity {

public:
  Character(glm::vec3 pos);
  virtual ~Character();

	void render() override;
	void update(float dt) override;

private:
  Node rootNode;
  Head head;
  Chest chest;
  LeftArm l_arm;
  RightArm r_arm;
  LeftLeg l_leg;
  RightLeg r_leg;

  GLuint tex;
  Loader texLoader;

  float animState;
};