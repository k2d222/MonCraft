#include "SliceMap.hpp"

SliceMap::SliceMap() {}

void SliceMap::insert(std::vector<Structure::Slice> const& slices) {
  std::lock_guard<std::mutex> lck(slicesMutex);
  for(auto slice : slices) {
    auto& dest = map[slice.cpos];
    dest.push_back(slice);
  }
}

std::vector<Structure::Slice> SliceMap::pop(glm::ivec3 cpos) {
  std::lock_guard<std::mutex> lck(slicesMutex);
  std::vector<Structure::Slice> slices = {};
  auto it = map.find(cpos);
  if(it != map.end()) {
    it->second.swap(slices);
    map.erase(it);
  }
  return slices;
}
