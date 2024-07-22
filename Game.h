#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

typedef struct Stats {
  unsigned int shapes;
  unsigned int score;
  unsigned int rows;
} Stats_t;

class Game {
public:
  Game();
  Game(Game &other) = delete;
  void operator=(const Game &) = delete;
  bool Init(const char *title, const int width, const int height);
  void HandleInput();
  void Update();
  void Render();
  void Run();
  ~Game();

private:
  Stats_t m_stats;
  SDL_Window *m_window;
  SDL_Renderer *m_renderer;
  void Close();
};
#endif
