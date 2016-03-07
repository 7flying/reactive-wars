#include <SFML/Graphics.hpp>
#include "GameStateInit.hpp"


GameStateInit::GameStateInit(Game *game)
{
    this->game = game;
    Vector2f pos = Vector2f(this->game->window.getSize());
    this->view.setSize(pos);
    pos *= 0.5f;
    this->view.setCenter(pos);
}

void GameStateInit::draw(const float dt)
{
    this->game->window.setView(this->view);
    this->game->window.clear(Color::Black);
    this->game->window.draw(this->game->background);
}

void GameStateInit::update(const float dt)
{
    
}

void GameStateInit::handleInput()
{
    
}

void GameStateInit::newGame()
{
    
}

void GameStateInit::loadGame()
{
  
}

void GameStateInit::credits()
{
    
}
