#pragma once

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <stdint.h>
#include <memory>

#include "controller/MouseController.hpp"
#include "save/ClientConfig.hpp"

namespace ui { class Root; }

/**
 * The viewport is an abstration layer for the whole opengl context.
 * Internally, it creates a SDL window and prepares the gl context.
 * It handles all keyboard / mouse events through controllers.
 * All SDL behavior is abstracted in the Viewport. Hence, the rest of the
 * program is gui-independent.
 */

class Viewport
{
public:

  /**
   * Creates the SDL window with the given dimensions.
   */
  Viewport(glm::ivec2 size);
  ~Viewport();

  static const int framerate; // fps in seconds
  static const int timePerFrame; // time per frame in millis

  /**
   * A frame update / draw must happen between a beginFrame() and endFrame().
   * beginFrame returns true if the program must quit.
   * a usual draw loop looks like the following:
   * for(vp.beginFrame(dt);;vp.endFrame()) { // update & draw // }
   */
  bool beginFrame(float& dt);
  void endFrame();

  void createRoot();
  ui::Root* getRoot();
  void captureMouse();
  void toggleVSync();
  void toggleFullscreen();
  void quit();

  glm::ivec2 size;

  MouseController mouseController;

private:
  void on_event(SDL_Event const& e);
  void on_window_event(SDL_WindowEvent const& e);
  void on_keydown(SDL_Keycode k);
  void on_keyup(SDL_Keycode k);
  void on_mousedown(SDL_MouseButtonEvent const& e);
  void on_mouseup(SDL_MouseButtonEvent const& e);

  SDL_Window* window;
  SDL_GLContext context;

  uint32_t timeBegin;
  uint32_t lastTime;

  bool mouseCaptured;
  bool vsync;
  bool fullscreen;
  bool mustQuit;

  std::unique_ptr<ui::Root> root;

  Config::ClientConfig config;
};
