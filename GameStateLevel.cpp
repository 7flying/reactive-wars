#include "GameStateLevel.hpp"


GameStateLevel::GameStateLevel(Game *game)
{
    this->game = game;
    Vector2f pos = Vector2f(this->game->window.getSize());
    this->gameView.setSize(pos);
    pos *= 0.5f;
    this->gameView.setCenter(pos);

    this->map = Map("city_map.dat", 64, 64, game->tileAtlas);

}

void GameStateLevel::draw(const float dt)
{
    this->game->window.clear(Color::Black);

    this->game->window.draw(this->game->background);
    this->game->window.setView(this->gameView);
    this->map.draw(this->game->window, dt);
}

void GameStateLevel::update(const float dt)
{
    
}

void GameStateLevel::handleInput()
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
            else if (event.key.code == Keyboard::R) {
                // Reload map
            }
            break;
        default:
            break;
        }
    }
}
