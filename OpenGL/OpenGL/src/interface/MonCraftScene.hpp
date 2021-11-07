#pragma once

#include "ui/Component.hpp"

#include "gl/Camera.hpp"
#include "controller/MouseController.hpp"
#include "controller/KeyboardController.hpp"
#include "multiplayer/client/Server.hpp"

#ifndef EMSCRIPTEN
  #include "audio/Music.hpp"
#endif

#include "terrain/World.hpp"
#include "gl/SkyBox.hpp"
#include "gl/ShadowMap.hpp"
#include "gl/Viewport.hpp"
#include "terrain/Renderer.hpp"
#include "interface/GameMenu.hpp"
#include "interface/Overlay.hpp"
#include "interface/DebugOverlay.hpp"

class MonCraftScene : public ui::Component {

public:
  MonCraftScene(Viewport* vp);

private:
  void updateFov(float dt);
  void updateShadowMaps();
  void updateUniforms(float t);
  void drawSkybox(float t);
  void drawEntities();
  void draw() override;

protected:
  virtual bool onMousePressed(glm::ivec2 pos) override;
  virtual bool onMouseMove(glm::ivec2 pos) override;
  virtual void onKeyPressed(Key k) override;
  virtual void onKeyReleased(Key k) override;
  virtual bool onActivate() override;

private:
  World& world;
  Config::ClientConfig& config;
  Renderer renderer;
  std::shared_ptr<Character> player;
  Identifier playerUid;

  // view controls
  Viewport* vp;
  Camera camera;
  KeyboardController keyboardController;

  // resources
  Shader* shader;
  Shader* fogShader;
  GLuint texAtlas;
  GLuint texCharacter;
  GLuint normalMapID[30];

  //interface
  std::unique_ptr<GameMenu> gameMenu;
  std::unique_ptr<DebugOverlay> debugOverlay;
  std::unique_ptr<Overlay> overlay;
  std::unique_ptr<ui::Image> middleDot;

public:
  // components
  SkyBox sky;
  Raycast caster;
  ShadowMap shadows;
  std::shared_ptr<Server> server;

  #ifndef EMSCRIPTEN
    Music musicPlayer;
  #endif

  // other parameters
  bool fogEnabled;
  const float sunSpeed;
  const float skyboxSpeed;
  glm::vec3 sunDir;
  bool captured;
};
