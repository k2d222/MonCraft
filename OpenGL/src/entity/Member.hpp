#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "Node.hpp"

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

  /**
   * The node holds the loc/rot/scale of this member.
   */
  Node node;

protected:
  glm::mat4 geometryModel;

  virtual std::unique_ptr<Mesh> createMesh() = 0;

private:
  std::unique_ptr<Mesh> mesh;
};
