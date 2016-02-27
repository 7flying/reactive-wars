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

    this->map = Map("city_map.dat", 64, 64, game->tileAtlas);
    this->zoomLevel = 1.0f;
    // center the camera on the map
    Vector2f center(this->map.width, this->map.height * 0.5);
    center *= float(this->map.tileSize);
    this->gameView.setCenter(center);

    this->actionState = ActionState::NONE;
}
    
void GameStateEditor::draw(const float dt)
{
    this->game->window.clear(Color::Black);

    this->game->window.setView(this->guiView);
    this->game->window.draw(this->game->background);

    this->game->window.setView(this->gameView);
    this->map.draw(this->game->window, dt);
}

void GameStateEditor::update(const float dt)
{
    
}

void GameStateEditor::handleInput()
{
    Event event;
    while (this->game->window.pollEvent(event)) {
        switch(event.type) {
        case Event::MouseMoved:{
            /* Pan the camera */
            if (this->actionState == ActionState::PANNING) {
                Vector2f pos = Vector2f(
                    Mouse::getPosition(this->game->window) - this->panningAnchor);
                this->gameView.move(-1.0f * pos * this->zoomLevel);
                this->panningAnchor = sf::Mouse::getPosition(this->game->window);
            }
            break;
        }
        case Event::MouseButtonPressed:{
            // Start panning
            if (event.mouseButton.button == Mouse::Middle) {
                if (this->actionState != ActionState::PANNING) {
                    this->actionState = ActionState::PANNING;
                    this->panningAnchor = Mouse::getPosition(this->game->window);
                }
            }
            break;
        }
        case Event::MouseButtonReleased:{
            // Stop panning
            if (event.mouseButton.button == sf::Mouse::Middle)
                this->actionState = ActionState::NONE;
            break;
        }
        case Event::MouseWheelMoved:{
            // Zoom the view 
            if (event.mouseWheel.delta < 0) {
                this->gameView.zoom(2.0f);
                this->zoomLevel *= 2.0f;
            }
            else {
                this->gameView.zoom(0.5f);
                this->zoomLevel *= 0.5f;
            }
            break;
        }
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
