/* funciona com SDL 2.0.5 e SDL2_gfx 1.0.3 */
#include <SDL2/SDL.h>
#include <SDL2_gfx/SDL2_gfxPrimitives.h>
#include <stdio.h>

#define LARGURA 800
#define ALTURA 600
#define RAIO 10

#define CIMA 1
#define BAIXO 2
#define ESQ 3
#define DIR 4

typedef struct ponto {
  int x, y;
  int r, d;
} Ponto;

void print_SDLError () {
  printf("SDL Error: %s\n", SDL_GetError());
}

int main () {
  SDL_Window* janela = NULL;
  SDL_Renderer* render = NULL;
  SDL_Event e;
  int fim = 0;
  Ponto p = { LARGURA / 2, ALTURA / 2, RAIO, CIMA };

  /* inicializa a SDL */
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Nao foi possivel inicializar a SDL!\n");
    print_SDLError();
    return 1;
  }

  /* inicializa a janela */
  janela = SDL_CreateWindow("Ponto Que Move", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            LARGURA, ALTURA, SDL_WINDOW_SHOWN);
  if (janela == NULL) {
    printf("Nao foi possivel criar a janela!\n");
    print_SDLError();
    return 2;
  }

  /* inicializa o renderizador */
  render = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (render == NULL) {
    SDL_DestroyWindow(janela);
    printf("Nao foi possivel criar o renderizador!\n");
    print_SDLError();
    return 3;
  }

  /* loop do "jogo" */
  while (!fim) {
    /* gerencia os eventos do "jogo" */
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT ||
         (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
        fim = 1;
      if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_UP && p.y > RAIO - 0) p.d = CIMA;
        else if (e.key.keysym.sym == SDLK_DOWN && p.y < ALTURA - RAIO) p.d = BAIXO;
        else if (e.key.keysym.sym == SDLK_LEFT && p.x > RAIO - 0) p.d = ESQ;
        else if (e.key.keysym.sym == SDLK_RIGHT && p.x < LARGURA - RAIO) p.d = DIR;
      }
    }

    /* desenha o ponto na tela */
    SDL_SetRenderDrawColor(render, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(render);
    filledCircleRGBA(render, p.x, p.y, p.r, 0, 255, 0, 255);
    SDL_RenderPresent(render);

    /* move o ponto e detecta colisoes */
    if (p.d == CIMA) {
      if (p.y > RAIO - 0) p.y = p.y - RAIO;
      else p.d = BAIXO;
    }
    else if (p.d == BAIXO) {
      if (p.y < ALTURA - RAIO) p.y = p.y + RAIO;
      else p.d = CIMA;
    }
    else if (p.d == ESQ) {
      if (p.x > RAIO - 0) p.x = p.x - RAIO;
      else p.d = DIR;
    }
    else {
      if (p.x < LARGURA - RAIO) p.x = p.x + RAIO;
      else p.d = ESQ;
    }

  }

  /* finaliza */
  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(janela);
  render = NULL;
  janela = NULL;
  SDL_Quit();

  return 0;
}
