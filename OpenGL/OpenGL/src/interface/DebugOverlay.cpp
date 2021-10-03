#include "DebugOverlay.hpp"
#include "gl/ResourceManager.hpp"

DebugOverlay::DebugOverlay(std::shared_ptr<Server> server) :
	server(server),
	world(World::getInst())
{
	auto font = ResourceManager::getFont("roboto");
	text_fps = std::make_unique<ui::Text>("Fps : ", font);;
	text_posPlayer = std::make_unique<ui::Text>("Pos : ", font);
	text_players = std::make_unique<ui::Text>("Players : ", font);
	text_uid = std::make_unique<ui::Text>("UID : ", font);
	text_gameTime = std::make_unique<ui::Text>("Time : ", font);

	pack(text_fps.get());
	pack(text_posPlayer.get());
	pack(text_players.get());
	pack(text_uid.get());
	pack(text_gameTime.get());
	setPadding(glm::ivec2(10));
	setGap(10);

	text_fps->setColor({ 1.0f, 1.0f, 1.0f, 1.f });
	text_fps->setAnchorY(ui::Anchor::END);
	text_fps->setFontSize(.35f);

	text_posPlayer->setColor({ 1.0f, 1.0f, 1.0f, 1.f });
	text_posPlayer->setAnchorY(ui::Anchor::END);
	text_posPlayer->setFontSize(.35f);

	text_players->setColor({ 1.0f, 1.0f, 1.0f, 1.f });
	text_players->setAnchorY(ui::Anchor::END);
	text_players->setFontSize(.35f);

	text_uid->setColor({ 1.0f, 1.0f, 1.0f, 1.f });
	text_uid->setAnchorY(ui::Anchor::END);
	text_uid->setFontSize(.35f);

	text_gameTime->setColor({ 1.0f, 1.0f, 1.0f, 1.f });
	text_gameTime->setAnchorY(ui::Anchor::END);
	text_gameTime->setFontSize(.35f);

}

void DebugOverlay::draw() {
	setSize(glm::ivec2(parent->getSize().x, 0));

	std::ostringstream text;
	text << "FPS : " << (int)(1.f / world.dt);
	text_fps->setText(text.str());

	text.str(""); // "clears" the string stream
	text << "Pos : " << std::fixed << std::setprecision(3) << server->getPlayer()->getPosition();
	text_posPlayer->setText(text.str());

	text.str(""); // "clears" the string stream
	text << "Players online : " << world.entities.count();
	text_players->setText(text.str());

	text.str(""); // "clears" the string stream
	text << "UID : " << server->getPlayer()->uid;
	text_uid->setText(text.str());

	text.str(""); // "clears" the string stream
	text << "Game Time : " << std::fixed << std::setprecision(3) << world.t;
	text_gameTime->setText(text.str());


	Box::draw();
}
