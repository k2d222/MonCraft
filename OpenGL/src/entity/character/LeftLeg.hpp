#pragma once

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "entity/Member.hpp"
#include "entity/Cube.hpp"
#include "gl/Mesh.hpp"

static const std::vector<GLfloat> leftLegUVs = {
  //TOP
  2 / 16.f, 5 / 16.f,
  1 / 16.f, 5 / 16.f,
  1 / 16.f, 4 / 16.f,
  2 / 16.f, 4 / 16.f,
  // BOTTOM
  3 / 16.f, 5 / 16.f,
  2 / 16.f, 5 / 16.f,
  2 / 16.f, 4 / 16.f,
  3 / 16.f, 4 / 16.f,
  // FRONT
  2 / 16.f, 5 / 16.f,
  1 / 16.f, 5 / 16.f,
  1 / 16.f, 8 / 16.f,
  2 / 16.f, 8 / 16.f,
  // RIGHT
  3 / 16.f, 5 / 16.f,
  2 / 16.f, 5 / 16.f,
  2 / 16.f, 8 / 16.f,
  3 / 16.f, 8 / 16.f,
  // BACK
  4 / 16.f, 5 / 16.f,
  3 / 16.f, 5 / 16.f,
  3 / 16.f, 8 / 16.f,
  4 / 16.f, 8 / 16.f,
  // LEFT
  1 / 16.f, 5 / 16.f,
  0 / 16.f, 5 / 16.f,
  0 / 16.f, 8 / 16.f,
  1 / 16.f, 8 / 16.f,
};

class LeftLeg : public Member {

public:
  LeftLeg() {
    glm::mat4 I(1.f);

    geometryModel = glm::scale(I, {4, 12, 4});
    geometryModel = glm::translate(I, {0, -6, 0}) * geometryModel;

    float zFightingOffset = 0.2f; // offset the legs slightly inwards and backwards
    geometryModel = glm::translate(I, {-zFightingOffset, 0, -zFightingOffset}) * geometryModel;

    node.loc = {2, -6, 0};
  }

protected:
  std::unique_ptr<Mesh> createMesh() override {
    return std::make_unique<Mesh>(Cube::vertices, Cube::normals, leftLegUVs, Cube::occlusions, Cube::indices, Cube::normalMap);
  }
};
