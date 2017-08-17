/* tela.c */

#include <stdio.h>
#include "tela.h"

void inicializa (char tela[ALTURA][LARGURA], Ponto* p) {
  int i, j;
  for (i = 0; i < ALTURA; i += (ALTURA - 1)) {
    for (j = 0; j < LARGURA; j++) {
      tela[i][j] = TETO_E_CHAO;
    }
  }
  for (i = 1; i < ALTURA - 1; i++) {
    for (j = 0; j < LARGURA; j += (LARGURA - 1)) {
      tela[i][j] = PAREDE;
    }
  }
  for (i = 1; i < ALTURA - 1; i++) {
    for (j = 1; j < LARGURA - 1; j++) {
      tela[i][j] = ESPACO;
    }
  }
  i = ALTURA / 2;
  j = LARGURA / 2;
  tela[i][j] = PONTO;
  p->x = i;
  p->y = j;
  p->d = SOBE;
}

void desenha (char tela[ALTURA][LARGURA]) {
  int i, j;
  for (i = 0; i < ALTURA; i++) {
    for (j = 0; j < LARGURA; j++) {
      printf("%c", tela[i][j]);
    }
    printf("\n");
  }
}

void move (char tela[ALTURA][LARGURA], Ponto* p) {
  if (p->d == SOBE) {
    if (p->x > 1) {
      sobe(tela, p);
    }
    else {
      p->d = DESCE;
      desce(tela, p);
    }
  }
  else if (p->d == DESCE) {
    if (p->x < ALTURA - 2) {
      desce(tela, p);
    }
    else {
      p->d = SOBE;
      sobe(tela, p);
    }
  }
  else if (p->d == ESQUERDA) {
    if (p->y > 1) {
      esquerda(tela, p);
    }
    else {
      p->d = DIREITA;
      direita(tela, p);
    }
  }
  else if (p->d == DIREITA) {
    if (p->y < LARGURA - 2) {
      direita(tela, p);
    }
    else {
      p->d = ESQUERDA;
      esquerda(tela, p);
    }
  }
}

void sobe (char tela[ALTURA][LARGURA], Ponto* p) {
  tela[p->x][p->y] = ESPACO;
  p->x--;
  tela[p->x][p->y] = PONTO;
}

void desce (char tela[ALTURA][LARGURA], Ponto* p) {
  tela[p->x][p->y] = ESPACO;
  p->x++;
  tela[p->x][p->y] = PONTO;
}

void esquerda (char tela[ALTURA][LARGURA], Ponto* p) {
  tela[p->x][p->y] = ESPACO;
  p->y--;
  tela[p->x][p->y] = PONTO;
}

void direita (char tela[ALTURA][LARGURA], Ponto* p) {
  tela[p->x][p->y] = ESPACO;
  p->y++;
  tela[p->x][p->y] = PONTO;
}

void muda_direcao (Ponto* p, int d) {
  if (d == 'a') {
    p->d = ESQUERDA;
  }
  else if (d == 's') {
    p->d = DESCE;
  }
  else if (d == 'd') {
    p->d = DIREITA;
  }
  else if (d == 'w') {
    p->d = SOBE;
  }
}
