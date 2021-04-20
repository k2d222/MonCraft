#pragma once
#include <iostream>
#include <chrono>
#include <glm/glm.hpp>

class DebugTimer {

  static std::chrono::time_point<std::chrono::high_resolution_clock> start;
  static float timeElapsed;

public:
  static void debug_timer_start();
  static void debug_timer_end();
  static float debug_timer_time();
};

#define TIME(exec)                                                           \
  {                                                                          \
    DebugTimer::debug_timer_start();                                         \
  }                                                                          \
  exec {                                                                     \
    DebugTimer::debug_timer_end();                                           \
    std::cout << #exec << " took " << DebugTimer::debug_timer_time() << "ms" \
              << std::endl;                                                  \
  }

template<typename T>
void debug_bindump(T val) {
  for(int i = 8 * sizeof(T) -1; i >= 0; i--) {
    std::cout << (val >> i & 1);
  }
  std::cout << std::endl;
}

template<typename T, glm::length_t N>
std::ostream& operator<<(std::ostream& os, glm::vec<N, T> const& v) {
  os << "vec" << N << "(";
  for(size_t i = 0; i < N-1; i++)
    os << v[i] << ", ";
  os << v[N-1] << ")";
  return os;
}