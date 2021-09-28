#pragma once

#include <thread>
#include <mutex>
#include <future>
#include <condition_variable>
#include <unordered_map>
#include <glm/glm.hpp>

#include "terrain/ChunkMap.hpp"
#include "SliceMap.hpp"
#include "ChunkGenerator.hpp"
#include "gl/Camera.hpp"
#include "util/PriorityList.hpp"
#include "util/AtomicCyclicList.hpp"
#include "terrain/World.hpp"


class TerrainGenerator
{
public:
  TerrainGenerator();
  ~TerrainGenerator();

  TerrainGenerator(TerrainGenerator const&) = delete;
  TerrainGenerator& operator=(TerrainGenerator const&) = delete;

  void startGeneration();
  void stopGeneration();
  void toggleGeneration();
  bool generating;

  void remOldChunks(glm::vec3 pos);

  static const int chunkSize = 16; // TODO: in a config file

  // TODO: should we use runtime alloc instead of compile-time ? Post release
  using WaitingList = AtomicCyclicList<glm::ivec3, 100000>;
  WaitingList waitingChunks; // chunk positions yet to be loaded

private:
  ChunkGenerator generator;

  // threading
  unsigned int threadCount;
  std::vector<std::thread> genWorkerThreads; // creates new chunks when it can
  std::mutex workerMutex;
  void genWorker();

  std::shared_ptr<Chunk> getOrGen(glm::ivec3 cpos);
  void setupNeighbors(std::shared_ptr<Chunk> chunk);
  void computeChunk(std::shared_ptr<Chunk> chunk);

  // utilities for workers
  bool sleepFor(std::chrono::milliseconds);
  void updateWaitingList();

  std::vector<glm::ivec3> busyList; // list of chunks beiing generated
  std::mutex busyListMutex;
  bool addToBusyList(glm::ivec3 cpos);
  void remFromBusyList(glm::ivec3 cpos);

  // signals to stop the threads
  bool stopFlag;
  std::mutex stopMutex;
  std::condition_variable stopSignal;

  // chunk storage
  World& world;
  SliceMap sliceMap; // hashmap to hold the slices generated by structures
};
