#pragma once

#include "util/DataStore.hpp"
#include "blocks/Block.hpp"
#include "Chunk.hpp"

/**
 * A structure allows the generation of complex block structures
 * that spans across chunks, e.g. trees.
 * /!\ The Structure cannot be larger than twice the chunk size.
 */

class Structure {
public:

  using BlockStore = DataStore<BlockType, 3>;

  struct Slice {
    std::shared_ptr<const BlockStore> store;
    glm::ivec3 cpos;
    glm::ivec3 off, start, end;
  };

  using slices_t = std::vector<Slice>;

  virtual ~Structure() = default;

  /**
   * Spawns a structure in a given chunk at given block position.
   * The block position is in range vec3(0) to chunkSize.
   */
  virtual slices_t spawn(Chunk& chunk, glm::ivec3 pos) const = 0;

  /**
   * Applies a slice to a given chunk.
   */
  static void applySlice(Chunk& chunk, Slice const& slice);
};


class Tree : public Structure {

public:
  Tree();
  slices_t spawn(Chunk& chunk, glm::ivec3 pos) const override;
  std::shared_ptr<BlockStore> store;
};

class Cactus : public Structure {

public:
    Cactus();
    slices_t spawn(Chunk& chunk, glm::ivec3 pos) const override;
    std::shared_ptr<BlockStore> store;
};
