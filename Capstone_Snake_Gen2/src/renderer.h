#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "enemy.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  //void Render(Snake const snake, SDL_Point const &food);
  void Render(Snake const snake,
               //Enemy const enemy,
               std::unique_ptr<Enemy> &enemy,
               SDL_Point const &food,
               const int &mode);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif