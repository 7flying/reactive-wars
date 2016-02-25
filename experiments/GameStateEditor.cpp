#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "GameStateEditor.hpp"


GameStateEditor::GameStateEditor(Game *game)
{
    this->game = game;
    Vector2f pos = Vector2f(this->game->window.getSize());
    this->guiView.setSize(pos);
    this->gameView.setSize(pos);
    pos *= 0.5f;
    this->guiView.setCenter(pos);
    this->gameView.setCenter(pos);
}
    
void GameStateEditor::draw(const float dt)
{
    this->game->window.clear(Color::Black);
    this->game->window.draw(this->game->background);
}

void GameStateEditor::update(const float dt)
{
    
}

void GameStateEditor::handleInput()
{
    Event event;
    while (this->game->window.pollEvent(event)) {
        switch(event.type) {
        case Event::Closed:{
            this->game->window.close();
            break;
        }
        case Event::Resized:{
            gameView.setSize(event.size.width, event.size.height);
            guiView.setSize(event.size.width, event.size.height);
            this->game->background.setPosition(
                this->game->window.mapPixelToCoords(Vector2i(0, 0),
                                                    this->guiView));
            this->game->background.setScale(
                float(event.size.width) / float(
                    this->game->background.getTexture()->getSize().x), 
                float(event.size.height) / float(
                    this->game->background.getTexture()->getSize().y));
            break;
        }
        default:
            break;
        }
    }
}
