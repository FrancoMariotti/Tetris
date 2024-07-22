#ifndef PIECE_H
#define PIECE_H

#include <SDL2/SDL.h>
#include "Board.h"
#include "utils.h"

const int Side = 20;
const int NSquares = 4;
const int Cos90 = 0;
const int Sin90 = 1;
const int SinMinus90 = -1;

typedef struct Square {
  int dx;
  int dy;
} Square_t;

typedef struct Direction {
  int x;
  int y;
} Direction_t;

const Direction_t Left = {-1, 0};
const Direction_t Right = {1, 0};


const int N_Pieces = 7;
const Square_t T_Piece[NSquares] = {{0, 1}, {1, 0}, {1, 1}, {2, 1}};
const Square_t O_Piece[NSquares] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
const Square_t I_Piece[NSquares] = {{0, 0}, {1, 0}, {2, 0}, {3, 0}};
const Square_t L_Piece[NSquares] = {{0, 1}, {1, 1}, {2, 1}, {2, 0}};
const Square_t J_Piece[NSquares] = {{0, 0}, {0, 1}, {1, 1}, {2, 1}};
const Square_t S_Piece[NSquares] = {{0, 1}, {1, 1}, {1, 0}, {2, 0}};
const Square_t Z_Piece[NSquares] = {{2, 1}, {1, 1}, {1, 0}, {0, 0}};

static const Square_t *pieces[N_Pieces] = {T_Piece, O_Piece, I_Piece, L_Piece,
                                           J_Piece, S_Piece, Z_Piece};

static const Square_t *get_piece() { return pieces[rand() % N_Pieces]; }

class Piece {
public:
  Piece(Board &m, SDL_Renderer *renderer);
  void HandleInput(SDL_Event &e);
  void Update();
  void Draw();
  ~Piece();

private:
  void Rotate(int sin);
  void MoveX(Direction_t dir);
  void RenderSquare(struct Square &square);
  void SetInitialState();

  struct Square squares[NSquares];
  int colorId;
  const Color_t* color;
  Board &b;
  SDL_Renderer *m_renderer;
  int x;
  int y;
  int yScreen;
  bool moving;
};
#endif
