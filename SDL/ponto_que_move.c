/* funciona com SDL 2.0.5 e SDL2_gfx 1.0.3 */
#include <SDL2/SDL.h>
#include <SDL2_gfx/SDL2_gfxPrimitives.h>
#include <stdio.h>

#define LARGURA 800
#define ALTURA 600

typedef enum direcao {
  CIMA,
  BAIXO,
  ESQUERDA,
  DIREITA,
} Direcao;

typedef struct ponto {
  int x, y;
  int raio;
  Direcao d;
} Ponto;

void print_SDLError () {
  printf("SDL Error: %s\n", SDL_GetError());
}

int main (int argc, char* argv[]) {
  SDL_Window* janela = NULL;
  SDL_Renderer* render = NULL;
  SDL_Event e;
  int fim = 0;
  Ponto p = { LARGURA / 2, ALTURA / 2, 10, CIMA };

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
    /* eventos do "jogo" - sair e mudar a direcao do ponto */
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT ||
         (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
        fim = 1;
      if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_UP && p.y > p.raio - 0) p.d = CIMA;
        else if (e.key.keysym.sym == SDLK_DOWN && p.y < ALTURA - p.raio) p.d = BAIXO;
        else if (e.key.keysym.sym == SDLK_LEFT && p.x > p.raio - 0) p.d = ESQUERDA;
        else if (e.key.keysym.sym == SDLK_RIGHT && p.x < LARGURA - p.raio) p.d = DIREITA;
      }
    }

    /* logica do "jogo" - move o ponto e detecta colisoes */
    if (p.d == CIMA) {
      /* se bateu no teto vai para baixo */
      if (p.y == p.raio) p.d = BAIXO;
      /* senao continua indo para cima */
      else p.y = p.y - p.raio;
    }
    else if (p.d == BAIXO) {
      /* se bateu no chao vai para cima */
      if (p.y == ALTURA - p.raio) p.d = CIMA;
      /* senao continua indo para baixo */
      else p.y = p.y + p.raio;
    }
    else if (p.d == ESQUERDA) {
      /* se bateu na parede esquerda vai para a direita */
      if (p.x == p.raio) p.d = DIREITA;
      /* senao continua indo para a esquerda */
      else p.x = p.x - p.raio;
    }
    else {
      /* se bateu na parede direita vai para a esquerda */
      if (p.x == LARGURA - p.raio) p.d = ESQUERDA;
      /* senao continua indo para a direita */
      else p.x = p.x + p.raio;
    }

    /* renderizacao do "jogo" - desenha o ponto na tela */
    SDL_SetRenderDrawColor(render, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(render);
    filledCircleRGBA(render, p.x, p.y, p.raio, 0x00, 0xFF, 0x00, 0xFF);
    SDL_RenderPresent(render);
  }

  /* finaliza */
  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(janela);
  render = NULL;
  janela = NULL;
  SDL_Quit();

  return 0;
}
