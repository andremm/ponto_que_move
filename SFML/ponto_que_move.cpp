/* funciona com SFML 2.4.2 */
#include <SFML/Graphics.hpp>

#define LARGURA 800
#define ALTURA 600
#define RAIO 10.f

enum direcao {
  CIMA,
  BAIXO,
  ESQUERDA,
  DIREITA,
};

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
    /* eventos do "jogo" - sair e mudar a direcao do ponto */
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
          direcao = ESQUERDA;
        else if (event.key.code == sf::Keyboard::Right && shape.getPosition().x < LARGURA - RAIO)
          direcao = DIREITA;
      }
    }

    /* logica do "jogo" - move o ponto e detecta colisoes */
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
    else if (direcao == ESQUERDA) {
      shape.setPosition(shape.getPosition().x-1,shape.getPosition().y);
      if (shape.getPosition().x < RAIO - 0)
        direcao = DIREITA;
    }
    else {
      shape.setPosition(shape.getPosition().x+1,shape.getPosition().y);
      if (shape.getPosition().x > LARGURA - RAIO)
        direcao = ESQUERDA;
    }

    /* renderizacao do "jogo" - desenha o ponto na tela */
    window.clear();
    window.draw(shape);
    window.display();

  }
  return 0;
}
