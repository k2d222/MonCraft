#pragma once

#include <SFML/Network.hpp>
#include <random>

/**
 * UUID for entities and other network-shared resources.
 */
class Identifier {
public:
  Identifier(sf::Uint64 id);
  static Identifier generate();

private:
  sf::Uint64 id;

  friend sf::Packet& operator<<(sf::Packet& packet, Identifier const& uid);
  friend sf::Packet& operator>>(sf::Packet& packet, Identifier& uid);
};
