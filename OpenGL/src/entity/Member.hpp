#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Node.hpp"
#include "util/AnimationMixer.hpp"

class Mesh;

/**
 * An entity's single body part.
 */

class Member {

public:
  Member();
  virtual ~Member();

  /**
   * Draws the member.
   */
  void draw();

  void animate(uint32_t dt);

  /**
   * The node holds the loc/rot/scale of this member.
   */
  Node node;

  std::unique_ptr<AnimationMixer> anim;

protected:
  glm::mat4 geometryModel;

  virtual std::unique_ptr<Mesh> createMesh() = 0;

private:
  std::unique_ptr<Mesh> mesh;
};
