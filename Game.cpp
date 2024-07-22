#include "Game.h"
#include "BitmapFont.h"
#include "Board.h"
#include "Piece.h"
#include "Timer.h"
#include <SDL2/SDL_image.h>

Game::Game() : m_stats({0, 0, 0}) {}

bool Game::Init(const char *title, const int width, const int height) {
  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = false;
  } else {
    m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED, width, height,
                                SDL_WINDOW_SHOWN);
    if (m_window == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      success = false;
    } else {
      m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
      if (m_renderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n",
               SDL_GetError());
        success = false;
      } else {
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
          printf("SDL_image could not initialize! SDL_image Error: %s\n",
                 IMG_GetError());
          success = false;
        }
      }
    }
  }

  return success;
}

void Game::HandleInput() {}

void Game::Update() {}

void Game::Render() {}

void Game::Close() {
  SDL_DestroyRenderer(m_renderer);
  SDL_DestroyWindow(m_window);
  IMG_Quit();
  SDL_Quit();
  return;
}

void Game::Run() {
  if (!m_renderer) {
    printf("Failed to initialize!\n");
  } else {
    bool quit = false;
    bool paused = false;
    SDL_Event e;
    LTimer timer;
    Board b(m_renderer, m_stats);
    Piece p(b, m_renderer);
    BitmapFont font(m_renderer, m_window);
    font.Build("./font2.png");

    const int SCREEN_FPS = 30;
    const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;
    //	Game Loop
    //	---------
    //	init
    //	handle_input
    //	update
    //	render
    //	run

    while (!quit) {
      timer.start();
      while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT)
          quit = true;

        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_p) {
          paused = !paused;
        }

        if (!paused)
          p.HandleInput(e);
      }

      if (paused) {
        SDL_Delay(SCREEN_TICKS_PER_FRAME);
        continue;
      }

      p.Update();
      b.Update();

      if (b.ToppedOut()) {
        quit = true;
        continue;
      }

      SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
      SDL_RenderClear(m_renderer);

      font.Render("Puntaje", 300, 0);
      font.Render(std::to_string(m_stats.score), 300, 50);
      b.Draw();
      p.Draw();

      SDL_RenderPresent(m_renderer);

      int frame_ticks = timer.getTicks();
      if (frame_ticks < SCREEN_TICKS_PER_FRAME) {
        SDL_Delay(SCREEN_TICKS_PER_FRAME - frame_ticks);
      }
    }
  }

  Close();
}

Game::~Game() {
  m_window = NULL;
  m_renderer = NULL;
}
