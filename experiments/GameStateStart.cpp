#include <SFML/Graphics.hpp>
#include "GameStateStart.hpp"
#include "GameStateEditor.hpp"
#include "GameState.hpp"


GameStateStart::GameStateStart(Game *game)
{
    this->game = game;
    Vector2f pos = Vector2f(this->game->window.getSize());
    this->view.setSize(pos);
    pos *= 0.5f;
    this->view.setCenter(pos);
}

void GameStateStart::draw(const float dt)
{
    this->game->window.setView(this->view);
    this->game->window.clear(Color::Black);
    this->game->window.draw(this->game->background);
}

void GameStateStart::update(const float dt)
{
    
}

void GameStateStart::handleInput()
{
    Event event;
    while (this->game->window.pollEvent(event)) {
        switch(event.type) {
        case Event::Closed:{
            game->window.close();
            break;
        }
        case Event::Resized:{
            this->view.setSize(event.size.width, event.size.height);
            this->game->background.setPosition(
                // Convert a position in window coordinates to its equivalent
                // position in world coordinates usint the current view
                this->game->window.mapPixelToCoords(Vector2i(0, 0)));
            this->game->background.setScale(
                float(event.size.width) / float(
                    this->game->background.getTexture()->getSize().x),
                float(event.size.width) / float(
                    this->game->background.getTexture()->getSize().y));
            break;
        }
        case Event::KeyPressed:{
            if (event.key.code == Keyboard::Escape)
                this->game->window.close();
            else if (event.key.code == Keyboard::Space)
                this->loadgame();
            break;
        }
        default:
            break;
        }
    }
}

void GameStateStart::loadgame()
{
    this->game->pushState(new GameStateEditor(this->game));
}
