#include <SFML/Graphics.hpp>
#include "GameStateInit.hpp"
#include "GameStateLevel.hpp"


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
    Event event;
    while (this->game->window.pollEvent(event)) {
        switch (event.type) {
        case Event::Closed:
            this->game->window.close();
            break;
        case Event::KeyPressed:
            if (event.key.code == Keyboard::Escape)
                this->game->window.close();
            else if (event.key.code == Keyboard::Insert) // TODO check Insert
                this->loadGame();
                                                
            break;
        default:
            break;
        }
    }
}

void GameStateInit::newGame()
{
    
}

void GameStateInit::loadGame()
{
    this->game->pushState(new GameStateLevel(this->game));
}

void GameStateInit::credits()
{
    
}
