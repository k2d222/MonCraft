#pragma once

#include <glm/glm.hpp>
#include "Chunk.hpp"
#include "../noise/Noise.hpp"

/**
* Generates new chunks.
*/

class Generator {
public:
  Generator(int chunkSize);

  /**
  * Generates a chunk at the given chunk index.
  */
  std::unique_ptr<Chunk> generate(glm::ivec3 pos) const;

private:
  int chunkSize;
  SimplexNoise noise;
  SimplexNoise noiseX;
  SimplexNoise noiseY;
  SimplexNoise noiseZ;
  ValueNoise treeNoise;
};
