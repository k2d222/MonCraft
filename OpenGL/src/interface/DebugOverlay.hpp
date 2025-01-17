#pragma once

#include <memory>

#include "ui/Box.hpp"
#include "ui/Text.hpp"

class Server;
class World;

class DebugOverlay : public ui::Box
{
public:
	DebugOverlay(std::shared_ptr<Server> server);
	void draw() override;

private:
	std::unique_ptr<ui::Text> text_fps;
	std::unique_ptr<ui::Text> text_posPlayer;
	std::unique_ptr<ui::Text> text_players;
	std::unique_ptr<ui::Text> text_uid;
	std::unique_ptr<ui::Text> text_gameTime;

	std::shared_ptr<Server> server;
	World& world;
};
