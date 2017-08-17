/* tela.h */

#ifndef TELA_H
#define TELA_H

#define ALTURA 10
#define LARGURA 50

#define PONTO '.'
#define ESPACO ' '
#define TETO_E_CHAO '-'
#define PAREDE '|'

typedef enum direcao {
  SOBE,
  DESCE,
  ESQUERDA,
  DIREITA
} Direcao;

typedef struct ponto {
  int x, y;
  Direcao d;
} Ponto;

void inicializa (char tela[ALTURA][LARGURA], Ponto* p);
void desenha (char tela[ALTURA][LARGURA]);
void move (char tela[ALTURA][LARGURA], Ponto* p);
void sobe (char tela[ALTURA][LARGURA], Ponto* p);
void desce (char tela[ALTURA][LARGURA], Ponto* p);
void esquerda (char tela[ALTURA][LARGURA], Ponto* p);
void direita (char tela[ALTURA][LARGURA], Ponto* p);
void muda_direcao (Ponto* p, int d);

#endif
