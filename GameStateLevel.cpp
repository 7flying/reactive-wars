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
    this->zoomLevel *= 0.5f;
    this->gameView.zoom(0.5f);
    // centre the camera
    sf::Vector2f centre(this->map.width, this->map.height * 0.5);
    centre *= float(this->map.tileSize);
    gameView.setCenter(centre);
    // the user is doing nothing
    this->actionState = ActionState::NONE;

    this->player = new Player(Vector2f(Vector2i(Game::WIN_WIDTH,
                                                Game::WIN_HEIGHT) / 2));
}

void GameStateLevel::draw(const Time dt)
{
    this->game->window.clear(Color::Black);

    this->game->window.setView(this->guiView);
    this->game->window.draw(this->game->background);

    this->game->window.setView(this->gameView);
    map.draw(this->game->window, dt.asSeconds());

    this->game->window.draw(*this->player->getSprite());
    for (auto b : this->player->bullets)
        this->game->window.draw(*b.getShape());
}

void GameStateLevel::update(const Time dt)
{
    this->player->getSprite()->move(
        *this->player->getMovement() * dt.asSeconds());
    if (this->player->getAnimStop())
        this->player->stopAnimation();
    this->player->getSprite()->update(dt);
    this->player->checkBullets(this->game->window.getSize());
    for (int i = 0; i < (int) this->player->bullets.size(); i++)
        this->player->bullets.at(i).update();
}

void GameStateLevel::handleInput()
{
    /*
    std::cout << "Position: x:"
              << this->player->getSprite()->getPosition().x
              << " y: " << this->player->getSprite()->getPosition().y
              << std::endl;
    std::cout << this->game->window.getSize().x << " "
              << this->game->window.getSize().y << std::endl;
    */
    Event event;
    while (this->game->window.pollEvent(event)) {
        switch (event.type) {
        case Event::Closed:
            this->game->window.close();
            break;
        case Event::KeyPressed:
            if (event.key.code == Keyboard::Escape)
                this->game->window.close();
            if (event.key.code == Keyboard::R) {
                // Reload map
                this->map.proceduralMap(Map::WIDTH, Map::HEIGHT,
                                        this->game->tileAtlas);
            }
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
        default:
            break;
        }
    }
    // Sprite movement
    bool stopAnim = true;
    this->player->getMovement()->x = 0;
    this->player->getMovement()->y = 0;
    if (Keyboard::isKeyPressed(Keyboard::A)) {
        this->player->changeAnimation(this->player->getAnimationLeft());
        this->player->getMovement()->x -= this->player->getSpeed();
        stopAnim = false;
    }
    if (Keyboard::isKeyPressed(Keyboard::D)) {
        this->player->changeAnimation(this->player->getAnimationRight());
        this->player->getMovement()->x += this->player->getSpeed();
        stopAnim = false;
    }
    if (Keyboard::isKeyPressed(Keyboard::W)) {
        this->player->changeAnimation(this->player->getAnimationUp());
        this->player->getMovement()->y -= this->player->getSpeed();
        stopAnim = false;
    }
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        this->player->changeAnimation(this->player->getAnimationDown());
        this->player->getMovement()->y += this->player->getSpeed();
        stopAnim = false;
    }
    this->player->setAnimStop(stopAnim);
    this->player->play();
    // Check if new bullets are fired
    int bulletx = 0, bullety = 0;
    bool fired = false;
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        bulletx = -1;
        fired = true;
    }
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        bulletx = 1;
        fired = true;
    }
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        bullety = -1;
        fired = true;
    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        bullety = 1;
        fired = true;
    }
    if (fired)
        this->player->fireBullet({bulletx, bullety});
}
