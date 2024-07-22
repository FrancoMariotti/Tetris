#include "Game.h"

const char *SCREEN_TITLE = "Tetris";
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *args[]) {
  Game game;
  game.Init(SCREEN_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT);
  game.Run();
  return 0;
}
