#include <glm/gtc/type_ptr.hpp>
#include <algorithm>

#include "World.hpp"
#include "gl/Shader.hpp"

using namespace glm;
using namespace std::chrono_literals;

World& World::getInst() {
  static World world;
  return world;
}

World::World()
{}

World::~World()
{}

void World::render(Camera const& camera) {
  std::vector<std::pair<float, std::shared_ptr<Chunk>>> toRender;

  chunks.for_each([&](std::shared_ptr<Chunk> chunk) {
    if(!chunk->hasData()) {
      chunk->update();
      return;
    }

    vec3 worldChunkPos = vec3(chunk->chunkPos * chunkSize);
    vec3 chunkCenter = worldChunkPos + vec3(chunkSize) / 2.f;
    vec4 posCamSpace = camera.view * vec4(chunkCenter, 1.0f);
    static const float tolerance = chunkSize * .5f * sqrt(3.f);

    if(camera.chunkInView(posCamSpace, tolerance)) {
      toRender.emplace_back(-posCamSpace.z, chunk);
    }
  });

  std::sort(toRender.begin(), toRender.end(), [](auto const& a, auto const& b) {
    return a.first > b.first; // sort back-to-front (far chunks first)
  });

  // draw solid
  for (auto iter = toRender.rbegin(); iter != toRender.rend(); ++iter) {
    auto& pair = *iter;
    pair.second->update();
    pair.second->drawSolid();
  }

  // draw transparent
  Shader* shader = Shader::getActive(); // TODO: find a better way
  GLint flags;
  glGetUniformiv(shader->program, shader->getUniform("flags"), &flags);
  flags = (flags & 0b1101) | 0b0010;
  glUniform1i(shader->getUniform("flags"), flags);

  auto viewDir = camera.center - camera.position;
  for(auto& pair : toRender) {
    pair.second->drawTransparent(viewDir);
  }

  flags = (flags & 0b1101) | 0b0000;
  glUniform1i(shader->getUniform("flags"), flags);
}

void World::renderSolid(Camera const& camera) {
  std::vector<std::pair<float, std::shared_ptr<Chunk>>> toRender;

  chunks.for_each([&](std::shared_ptr<Chunk> chunk) {
    if(!chunk->hasData()) {
      chunk->update();
      return;
    }

    vec3 worldChunkPos = vec3(chunk->chunkPos * chunkSize);
    vec3 chunkCenter = worldChunkPos + vec3(chunkSize) / 2.f;
    vec4 posCamSpace = camera.view * vec4(chunkCenter, 1.0f);
    static const float tolerance = chunkSize * .5f * sqrt(3.f);

    if(camera.chunkInView(posCamSpace, tolerance)) {
      toRender.emplace_back(-posCamSpace.z, chunk);
    }
  });

  std::sort(toRender.begin(), toRender.end(), [](auto& a, auto& b) {
    return a.first < b.first; // sort front-to-back (near chunks first)
  });

  for(auto& pair : toRender) {
    pair.second->drawAllAsSolid();
  }
}

Block* World::getBlock(ivec3 pos) {
  ivec3 cpos = floor(vec3(pos) / float(chunkSize));

  if(auto chunk = chunks.find(cpos)) {
    ivec3 dpos = pos - cpos * chunkSize;
    return chunk->at(dpos).get();
  }

  return nullptr;
}

bool World::setBlock(ivec3 pos, Block::unique_ptr_t block) {
  ivec3 cpos = floor(vec3(pos) / float(chunkSize));

  auto chunk = chunks.find(cpos);
  if(!chunk) return false;

  ivec3 dpos = pos - cpos * chunkSize;
  chunk->setBlock(dpos, std::move(block));
  return true;
}
