#ifndef BITMAP_H
#define BITMAP_H

#import "Texture.h"
#include <SDL2/SDL.h>

class BitmapFont {
public:
  BitmapFont(SDL_Renderer *renderer, SDL_Window *window);
  bool Build(const std::string &path);
  void Render(const std::string &text, int x, int y);
  ~BitmapFont();

private:
  // ASCII chars
  SDL_Rect charsRects[96];
  Texture fontTexture;
};

#endif
