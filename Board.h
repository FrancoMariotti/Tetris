#ifndef Board_H
#define Board_H

#include "Game.h"
#include "stdbool.h"
#include "utils.h"

const int Rows = 20;
const int Columns = 10;
const int Empty = -1;

class Board {
public:
  Board(SDL_Renderer *renderer, Stats_t &stats);
  void Update();
  void Draw();
  bool ToppedOut();
  bool CanMove(const unsigned int x, const unsigned int y);
  void Occupy(const int x, const int y, const int color);
  ~Board();

private:
  void NaiveLineClear();
  bool toppedOut;
  int xOrigin;
  int yOrigin;
  int row_count[Rows];
  int matrix[Rows][Columns];
  SDL_Renderer *m_renderer;
  Stats_t &m_stats;
};
#endif
