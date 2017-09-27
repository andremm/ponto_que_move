local altura, largura, ponto

function love.load ()
  love.window.setTitle("ponto que move")
  largura, altura = love.window.getMode()
  ponto = {
    modo = "fill",
    x = largura / 2,
    y = altura / 2,
    raio = 10,
    direcao = "cima",
  }
end

function love.update (dt)
  if love.keyboard.isDown("escape") then
    love.event.quit()
  elseif love.keyboard.isDown("up") and ponto.y > ponto.raio then
    ponto.direcao = "cima"
  elseif love.keyboard.isDown("down") and ponto.y < altura - ponto.raio then
    ponto.direcao = "baixo"
  elseif love.keyboard.isDown("left") and ponto.x > ponto.raio then
    ponto.direcao = "esquerda"
  elseif love.keyboard.isDown("right") and ponto.x < largura - ponto.raio then
    ponto.direcao = "direita"
  end

  if ponto.direcao == "cima" then
    if ponto.y == ponto.raio then
      ponto.direcao = "baixo"
    else
      ponto.y = ponto.y - ponto.raio
    end
  elseif ponto.direcao == "baixo" then
    if ponto.y == altura - ponto.raio then
      ponto.direcao = "cima"
    else
      ponto.y = ponto.y + ponto.raio
    end
  elseif ponto.direcao == "esquerda" then
    if ponto.x == ponto.raio then
      ponto.direcao = "direita"
    else
      ponto.x = ponto.x - ponto.raio
    end
  else
    if ponto.x == largura - ponto.raio then
      ponto.direcao = "esquerda"
    else
      ponto.x = ponto.x + ponto.raio
    end
  end
end

function love.draw ()
  love.graphics.setColor(0, 255, 0)
  love.graphics.circle(ponto.modo, ponto.x, ponto.y, ponto.raio)
end
