#include "BitmapFont.h"

BitmapFont::BitmapFont(SDL_Renderer *renderer, SDL_Window *window)
    : fontTexture(renderer, window) {};

bool BitmapFont::Build(const std::string &path) {
  bool success = true;

  if (!fontTexture.LoadFromFile(path)) {
    printf("Failed to load bitmap font texture");
    success = false;
  }

  int textureWidth = fontTexture.getWidth();
  int textureHeight = fontTexture.getHeight();

  // arranca desde 32 que es SPACE
  // y va hasta 126 que es ~
  int cellW = textureWidth / 16;
  int cellH = textureHeight / 6;

  for (int i = 0; i < 96; i++) {
    charsRects[i].x = 0;
    charsRects[i].y = 0;
    charsRects[i].w = cellW;
    charsRects[i].h = cellH;
  }

  int currentChar = 0;
  // int currentChar = 32;

  for (int row = 0; row < 6; row++) {
    for (int col = 0; col < 16; col++) {
      charsRects[currentChar].x = col * cellW;
      charsRects[currentChar].y = row * cellH;
      currentChar++;
    }
  }

  return success;
}

void BitmapFont::Render(const std::string &text, int x, int y) {
  for (int i = 0; i < text.length(); i++) {
    SDL_Rect &clip = charsRects[text[i] - 32];
    fontTexture.Draw(x + i * clip.w, y, &clip);
  }
}

BitmapFont::~BitmapFont() {};
