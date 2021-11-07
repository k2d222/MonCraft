#pragma once

#include <string>
#include <SFML/Network.hpp>
#include <glm/glm.hpp>
#include <functional>
#include "util/Identifier.hpp"
#include "../Packet.hpp"
#include "entity/character/Character.hpp"
#include "Server.hpp"
#include "multiplayer/terrain/PendingChunks.hpp"

class RealServer: public Server {

public:
  RealServer(std::string url, unsigned short port);
  virtual ~RealServer();

  void ping() override;
  void update() override;
  bool login() override;

  /**
   * Returns nullptr if the player was not created.
   */
  std::shared_ptr<Character> getPlayer() override;

  /**
  * Returns 0 if the player was not created.
  */
  Identifier getUid() override;

private:
  void packet_login();
  void packet_logout();
  void packet_ping();
  void packet_player_tick();
  void packet_blocks();
  void packet_chunks();
  void packet_ack_chunks(std::vector<glm::ivec3> chunks);
  void handle_logout(sf::Packet& packet);
  void handle_blocks(sf::Packet& packet);
  void handle_chunks(sf::Packet& packet);
  void handle_entity_tick(sf::Packet& packet);
  bool poll();


  sf::IpAddress addr;
  unsigned short port;
  sf::UdpSocket socket;
  sf::Time lastUpdate;
  const sf::Time frameDuration;
  sf::Clock clock;
  World& world;
  std::shared_ptr<Character> player;
  Identifier playerUid;
  PendingChunks pendingChunks;

  bool serverAck;
  sf::Time lastServerUpdate;
  const sf::Time timeout = sf::seconds(10);
};
