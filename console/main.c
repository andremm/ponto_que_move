/* main.c */

#include <stdio.h>
#include <stdlib.h>
#include "tela.h"

#ifdef _WIN32
  #include <windows.h>
  #include <conio.h>
  #define limpa_tela() system("cls")
  #define dorme(milis) Sleep(milis)
#else
  #include <unistd.h>
  #include "console.h"
  #define limpa_tela() system("clear")
  #define dorme(milis) usleep(milis * 1000)
#endif

int main () {

  char tela[ALTURA][LARGURA];
  int tecla = 0;
  Ponto p;

  inicializa(tela, &p);

  while (tecla != 27) {
    limpa_tela();
    desenha(tela);
    if (kbhit()) {
      tecla = getch();
      muda_direcao(&p, tecla);
    }
    move(tela, &p);
    dorme(1);
  }

  return 0;
}
