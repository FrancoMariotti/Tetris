#include "Board.h"
#include "Piece.h"
#include "utils.h"

Board::Board(SDL_Renderer *renderer, Stats_t &stats)
    : xOrigin(Side), yOrigin(0), toppedOut(false), m_renderer(renderer),
      m_stats(stats) {
  for (int y = 0; y < Rows; y++) {
    row_count[y] = 0;

    for (int x = 0; x < Columns; x++)
      matrix[y][x] = Empty;
  }
}

bool Board::ToppedOut() { return toppedOut; }

void Board::Occupy(const int x, const int y, const int color) {
  if (y < 0) {
    toppedOut = true;
    return;
  }

  row_count[y] += 1;
  matrix[y][x] = color;
}

bool Board::CanMove(unsigned int x, unsigned int y) {
  if (y >= Rows || x < 0 || x >= Columns)
    return false;

  return (matrix[y][x] == Empty);
}

void Board::NaiveLineClear() {
  // consider using binary operations to detect which lines should be cleared
  // this implies changing the representation of the board/Board
  int y;
  int x;
  int starting_row = -1;
  int end_row = -1;
  unsigned int start_deleting = 0;
  unsigned int rows_deleted = 0;

  for (y = 0; y < Rows; y++) {
    if (row_count[y] < Columns)
      continue;

    if (starting_row < 0)
      starting_row = y;

    end_row = y;
  }

  if (starting_row < 0)
    return;

  rows_deleted = end_row - starting_row + 1;
  m_stats.score += rows_deleted;

  // Move rows above start deletion point rows_deleted down
  for (y = starting_row - 1; (y >= 0 && row_count[y] > 0); y--) {
    start_deleting = y;
    row_count[y + rows_deleted] = row_count[y];

    for (x = 0; x < Columns; x++)
      matrix[y + rows_deleted][x] = matrix[y][x];
  }

  // Clear the top rows that were moved down
  for (y = 0; y < rows_deleted; y++) {
    row_count[start_deleting + y] = 0;

    for (x = 0; x < Columns; x++) {
      matrix[start_deleting + y][x] = Empty;
    }
  }
}

void Board::Update() { NaiveLineClear(); }

void Board::Draw() {
  int y = 0;
  int x = 0;
  const int spacing = 2;
  const int wallSide = Side + spacing;
  SDL_Rect boardCell = {0, 0, Side, Side};
  SDL_Rect boardWall = {0, 0, wallSide, wallSide};

  for (y = 0; y < Rows; y++) {
    // Left border
    boardWall.y = y * wallSide;
    SDL_SetRenderDrawColor(m_renderer, Grey.red, Grey.green, Grey.blue, 0xFF);
    SDL_RenderFillRect(m_renderer, &boardWall);

    //  Board cells
    for (x = 0; x < Columns; x++) {
      if (matrix[y][x] == Empty)
        continue;
      const Color_t *rectColor = getColor(matrix[y][x]);
      boardCell.x = x * (Side + spacing) + xOrigin + spacing;
      boardCell.y = y * (Side + spacing) + yOrigin + spacing;
      SDL_SetRenderDrawColor(m_renderer, rectColor->red, rectColor->green,
                             rectColor->blue, 0xFF);
      SDL_RenderFillRect(m_renderer, &boardCell);
    }

    // Right Border
    boardWall.x = (Columns + 1) * wallSide - spacing;
    SDL_SetRenderDrawColor(m_renderer, Grey.red, Grey.green, Grey.blue, 0xFF);
    SDL_RenderFillRect(m_renderer, &boardWall);
    boardWall.x = 0;
  }

  SDL_SetRenderDrawColor(m_renderer, Grey.red, Grey.green, Grey.blue, 0xFF);

  // Bottom Border
  boardWall.y = Rows * wallSide;
  for (x = 0; x < Columns + 1; x++) {
    boardWall.x = x * wallSide;
    SDL_RenderFillRect(m_renderer, &boardWall);
  }

  boardWall.w = Side;
  boardWall.x = (Columns + 1) * wallSide;
  SDL_RenderFillRect(m_renderer, &boardWall);
}

Board::~Board() {}
