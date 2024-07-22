#ifndef Texture_H
#define Texture_H

#include "string"
#include <SDL2/SDL.h>

class Texture {
public:
  Texture(SDL_Renderer *renderer, SDL_Window *window);
  bool LoadFromFile(std::string path);
  void Draw(int x, int y, SDL_Rect *clip);
  Uint32 getPixel(Uint32 x, Uint32 y);
  Uint32 getPitch();
  int getWidth();
  int getHeight();
  ~Texture();

private:
  SDL_Surface *surface;
  SDL_Texture *texture;
  SDL_Renderer *m_renderer;
  SDL_Window *m_window;
  int w;
  int h;
};
#endif
