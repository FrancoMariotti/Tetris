#include "Piece.h"
#include "Board.h"
#include "utils.h"

static const int PieceVel = 1;
static const int PieceInitialPos = -2;

void Piece::SetInitialState() {
  moving = false;
  x = (Columns - NSquares) / 2;
  y = PieceInitialPos;
  yScreen = y * Side;
  colorId = getColorId();
  color = getColor(colorId);
  const Square_t *piece = get_piece();
  for (int i = 0; i < NSquares; i++) {
    squares[i].dx = piece[i].dx;
    squares[i].dy = piece[i].dy;
  }
}

Piece::Piece(Board &b, SDL_Renderer *renderer) : b(b), m_renderer(renderer) {
  SetInitialState();
}

void Piece::Update() {
  if (moving && yScreen / (Side + 2) < y) {
    yScreen += PieceVel;
    return;
  }

  bool canMove = true;
  y++;

  for (int i = 0; (canMove && i < NSquares); i++) {
    int newY = y + squares[i].dy;
    if (newY < 0)
      continue;
    canMove = b.CanMove(x + squares[i].dx, newY);
  }

  if (!canMove) {
    y--;

    for (int i = 0; i < NSquares; i++) {
      b.Occupy(x + squares[i].dx, y + squares[i].dy, colorId);
    }

    SetInitialState();
  } else {
    moving = true;
  }
};

void Piece::Rotate(int sin) {
  // consider saving in an array the fixed positions of the rotation
  // that way the rotation is just accessing a position in an array
  // to get the new positions
  for (int i = 0; i < NSquares; i++) {
    int pointX = squares[i].dx;
    int pointY = squares[i].dy;

    pointY *= -1;

    pointY += 1;
    pointX -= 1;

    if (pointX == 0 && pointY == 0)
      continue;

    int newX = Cos90 * pointX - sin * pointY;
    int newY = sin * pointX + Cos90 * pointY;

    pointX = newX;
    pointY = newY;

    pointY -= 1;
    pointX += 1;

    pointY *= -1;

    squares[i].dx = pointX;
    squares[i].dy = pointY;
  }
}

void Piece::MoveX(Direction dir) {
  int prev_x = x;
  x += dir.x;

  bool canMove = true;
  canMove &= b.CanMove(x + squares[0].dx, y + squares[0].dy);
  canMove &= b.CanMove(x + squares[1].dx, y + squares[1].dy);
  canMove &= b.CanMove(x + squares[2].dx, y + squares[2].dy);
  canMove &= b.CanMove(x + squares[3].dx, y + squares[3].dy);

  if (!canMove)
    x = prev_x;
}

void Piece::HandleInput(SDL_Event &e) {
  if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
    switch (e.key.keysym.sym) {
    case SDLK_LEFT:
      MoveX(Left);
      break;
    case SDLK_RIGHT:
      MoveX(Right);
      break;
    case SDLK_UP:
      Rotate(Sin90);
      break;
    case SDLK_DOWN:
      Rotate(SinMinus90);
      break;
    }
  }
}

void Piece::Draw() {
  for (int i = 0; i < NSquares; i++) {
    // render squares
    int xRect = (x + squares[i].dx) * (Side + 2) + 20 + 2;
    int yRect = yScreen + squares[i].dy * (Side + 2);
    SDL_Rect fillRect = {xRect, yRect, Side, Side};
    SDL_SetRenderDrawColor(m_renderer, color->red, color->green, color->blue,
                           0xFF);
    SDL_RenderFillRect(m_renderer, &fillRect);
  }
}

Piece::~Piece() {}
