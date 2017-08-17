/* funciona com SFML 2.4.2 */
#include <SFML/Graphics.hpp>

#define LARGURA 800
#define ALTURA 600
#define RAIO 10.f

#define CIMA 1
#define BAIXO 2
#define ESQ 3
#define DIR 4

int main() {
  /* cria a janela */
  sf::RenderWindow window(sf::VideoMode(LARGURA, ALTURA), "Ponto Que Move");
  /* cria o ponto */
  sf::CircleShape shape(RAIO);
  int direcao = CIMA;
  shape.setFillColor(sf::Color::Green);
  shape.setPosition(LARGURA/2,ALTURA/2);
  shape.setRadius(RAIO);
  shape.setOrigin(RAIO, RAIO);

  /* loop do "jogo" */
  while (window.isOpen()) {
    /* gerencia os eventos do "jogo" */
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed ||
          (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
        window.close();
        break;
      }
      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up && shape.getPosition().y > RAIO - 0)
          direcao = CIMA;
        else if (event.key.code == sf::Keyboard::Down && shape.getPosition().y < ALTURA - RAIO)
          direcao = BAIXO;
        else if (event.key.code == sf::Keyboard::Left && shape.getPosition().x > RAIO - 0)
          direcao = ESQ;
        else if (event.key.code == sf::Keyboard::Right && shape.getPosition().x < LARGURA - RAIO)
          direcao = DIR;
      }
    }

    /* desenha o ponto na tela */
    window.clear();
    window.draw(shape);
    window.display();

    /* move o ponto e detecta colisoes */
    if (direcao == CIMA) {
      shape.setPosition(shape.getPosition().x,shape.getPosition().y-1);
      if (shape.getPosition().y < RAIO - 0)
        direcao = BAIXO;
    }
    else if (direcao == BAIXO) {
      shape.setPosition(shape.getPosition().x,shape.getPosition().y+1);
      if (shape.getPosition().y > ALTURA - RAIO)
        direcao = CIMA;
    }
    else if (direcao == ESQ) {
      shape.setPosition(shape.getPosition().x-1,shape.getPosition().y);
      if (shape.getPosition().x < RAIO - 0)
        direcao = DIR;
    }
    else {
      shape.setPosition(shape.getPosition().x+1,shape.getPosition().y);
      if (shape.getPosition().x > LARGURA - RAIO)
        direcao = ESQ;
    }
  }
  return 0;
}
