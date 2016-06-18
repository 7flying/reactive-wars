#include "GameStateLevel.hpp"


GameStateLevel::GameStateLevel(Game *game)
{
    this->game = game;
    Vector2f pos = Vector2f(this->game->window.getSize());
    this->gameView.setSize(pos);
    this->guiView.setSize(pos);
    pos *= 0.5f;
    this->gameView.setCenter(pos);
    this->guiView.setCenter(pos);

    this->map = Map("city_map.dat", Map::WIDTH, Map::HEIGHT, game->tileAtlas);

    // initialise zoom to 1
    this->zoomLevel = 1.0f;
    // centre the camera
    sf::Vector2f centre(this->map.width, this->map.height * 0.5);
    centre *= float(this->map.tileSize);
    gameView.setCenter(centre);
    // the user is doing nothing
    this->actionState = ActionState::NONE;

    this->player = new Player(Vector2f(Vector2i(Game::WIN_WIDTH,
                                                Game::WIN_HEIGHT) / 2));
}

void GameStateLevel::draw(const float dt)
{
    this->game->window.clear(Color::Black);

    this->game->window.setView(this->guiView);
    this->game->window.draw(this->game->background);

    this->game->window.setView(this->gameView);
    map.draw(this->game->window, dt);

    this->game->window.draw(*this->player->getSprite());
}

void GameStateLevel::update(const float dt)
{
    this->player->play();
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
                this->map.proceduralMap(Map::WIDTH, Map::HEIGHT,
                                        this->game->tileAtlas);
            } else if (event.key.code == Keyboard::Left)
                map.units[0].sprite.move(-10, 0);
            else if (event.key.code == Keyboard::Right)
                map.units[0].sprite.move(10, 0);
            else if (event.key.code == Keyboard::Up)
                map.units[0].sprite.move(0, -10);
            else if(event.key.code == Keyboard::Down) {
                map.units[0].sprite.move(0, 10);
                
            }
            this->game->window.draw(map.units[0].sprite);
            this->game->window.display();
            break;
        case Event::MouseMoved:
            /* Pan the camera */
            if (this->actionState == ActionState::PANNING) {
                Vector2f pos = sf::Vector2f(
                    Mouse::getPosition(this->game->window) - this->panningAnchor);
                gameView.move(-1.0f * pos * this->zoomLevel);
                panningAnchor = Mouse::getPosition(this->game->window);
            }
            break;
        case Event::MouseButtonPressed:
            /* Start panning */
            if (event.mouseButton.button == Mouse::Middle) {
                if (this->actionState != ActionState::PANNING) {
                    this->actionState = ActionState::PANNING;
                    this->panningAnchor = Mouse::getPosition(this->game->window);
                }
            }
            break;
        case Event::MouseButtonReleased:
            /* Stop panning */
            if (event.mouseButton.button == Mouse::Middle) {
                this->actionState = ActionState::NONE;
            }
            break;
            /* Zoom the view */
        case Event::MouseWheelMoved:
            if (event.mouseWheel.delta < 0) {
                gameView.zoom(2.0f);
                zoomLevel *= 2.0f;
            } else {
                gameView.zoom(0.5f);
                zoomLevel *= 0.5f;
            }
            break;
        case Event::Resized:
            gameView.setSize(event.size.width, event.size.height);
            gameView.zoom(zoomLevel);
            break;
            /* Sprite movement */
            
        default:
            break;
        }
    }
}
