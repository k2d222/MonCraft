#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "entity/Member.hpp"
#include "entity/Cube.hpp"
#include "gl/Mesh.hpp"

static const std::vector<GLfloat> leftArmUVs= {
  //TOP
  12 / 16.f, 5 / 16.f,
  11 / 16.f, 5 / 16.f,
  11 / 16.f, 4 / 16.f,
  12 / 16.f, 4 / 16.f,
  // BOTTOM
  13 / 16.f, 5 / 16.f,
  12 / 16.f, 5 / 16.f,
  12 / 16.f, 4 / 16.f,
  13 / 16.f, 4 / 16.f,
  // FRONT
  12 / 16.f, 5 / 16.f,
  11 / 16.f, 5 / 16.f,
  11 / 16.f, 8 / 16.f,
  12 / 16.f, 8 / 16.f,
  // RIGHT
  13 / 16.f, 5 / 16.f,
  12 / 16.f, 5 / 16.f,
  12 / 16.f, 8 / 16.f,
  13 / 16.f, 8 / 16.f,
  // BACK
  14 / 16.f, 5 / 16.f,
  13 / 16.f, 5 / 16.f,
  13 / 16.f, 8 / 16.f,
  14 / 16.f, 8 / 16.f,
  // LEFT
  11 / 16.f, 5 / 16.f,
  10 / 16.f, 5 / 16.f,
  10 / 16.f, 8 / 16.f,
  11 / 16.f, 8 / 16.f,
};

class LeftArm : public Member {

public:
  LeftArm() {
    glm::mat4 I(1.f);

    geometryModel = glm::scale(I, {4, 12, 4});
    geometryModel = glm::translate(I, {0, -4, 0}) * geometryModel;

    node.loc = {6, 4, 0};
  }

protected:
  std::unique_ptr<Mesh> createMesh() override {
    return std::make_unique<Mesh>(Cube::vertices, Cube::normals, leftArmUVs, Cube::occlusions, Cube::indices, Cube::normalMap);
  }
};
