#include "Texture.h"
#include <SDL2/SDL_image.h>

Texture::Texture(SDL_Renderer *renderer, SDL_Window *window)
    : m_renderer(renderer), m_window(window), texture(NULL) {}

bool Texture::LoadFromFile(std::string path) {
  SDL_Texture *newTexture = NULL;
  SDL_Surface *loadedSurface = IMG_Load(path.c_str());

  if (loadedSurface == NULL) {
    printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(),
           IMG_GetError());
  } else {
    surface = SDL_ConvertSurfaceFormat(loadedSurface,
                                       SDL_GetWindowPixelFormat(m_window), 0);
    newTexture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
    if (newTexture == NULL) {
      printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(),
             SDL_GetError());
    }

    w = loadedSurface->w;
    h = loadedSurface->h;

    SDL_FreeSurface(loadedSurface);
  }

  texture = newTexture;
  return (newTexture != NULL);
}

void Texture::Draw(int x, int y, SDL_Rect *clip = NULL) {
  // Set rendering space and render to screen
  SDL_Rect renderQuad = {x, y};
  if (clip) {
    renderQuad.w = clip->w;
    renderQuad.h = clip->h;
  }

  SDL_RenderCopy(m_renderer, texture, clip, &renderQuad);
}

Uint32 Texture::getPixel(Uint32 x, Uint32 y) {
  Uint32 *pixels = static_cast<Uint32 *>(surface->pixels);
  return pixels[(y * getPitch()) + x];
}

Uint32 Texture::getPitch() {
  if (!surface)
    return 0;
  return surface->pitch / 4;
}

int Texture::getWidth() { return w; }

int Texture::getHeight() { return h; }

Texture::~Texture() {
  if (texture != NULL) {
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    surface = NULL;
    texture = NULL;
    w = 0;
    h = 0;
  }
}
