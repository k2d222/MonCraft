#pragma once

#include <glm/glm.hpp>
#include <vector>

/**
 * A node is a geometry point in space. It holds a position, location and scale
 * and can be hierarchical, i.e. can have children, which will apply their
 * transform in their parent's local space.
 */

class Node {

public:
  Node();

  /**
   * read/write parameters of the node. Invalidates the model.
   */
  glm::vec3 loc;
  glm::vec3 rot;
  glm::vec3 sca;

  /**
   * The node model is computed when the root node calls update().
   * /!\ this is readonly
   */
  glm::mat4 model;

  /**
   * A root node may call update() to compute its model and recursively all of
   * the children models.
   */
  void update();

  /**
   * Adds a Node child to this node.
   * /!\ the child lifetime is not managed by the node and must exceed or equal
   * this node's lifetime.
   */
  void addChild(Node* child);

private:
  void computeTransforms(glm::mat4 parentModel);
  std::vector<Node*> children;
};
