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
    // Load player
    this->player = new Player(Vector2f(Vector2i(Game::WIN_WIDTH,
                                                Game::WIN_HEIGHT) / 2));
    // Setup points & level
    this->level = 1;
    this->points = 0;
    // enemies
    this->rng.seed(random_device()());
    for (int i = 0; i < (int) this->level * 4; i++)
        this->loadEnemy(i);
    for (int i = 0; i < (int) this->level * 2; i++)
        this->loadEnemy(0, true);
}

void GameStateLevel::draw(const Time dt)
{
    this->game->window.clear(Color::Black);

    this->game->window.setView(this->guiView);
    this->game->window.draw(this->game->background);

    this->game->window.setView(this->gameView);
    map.draw(this->game->window, dt.asSeconds());

    // Draw player
    this->game->window.draw(*this->player->getSprite());
    // Draw enemies
    for (int i = 0; i < (int) this->soldiers.size(); i++)
        this->game->window.draw(*this->soldiers.at(i)->getSprite());
    for (int i = 0; i < (int) this->skeletons.size(); i++)
        this->game->window.draw(*this->skeletons.at(i)->getSprite());
    // Draw bullets
    for (auto b : this->player->bullets)
        this->game->window.draw(*b.getShape());
}

void GameStateLevel::update(const Time dt)
{
    // Play player
    this->player->play();
    // Play soldiers
    for (int i = 0; i < (int) this->soldiers.size(); i++)
        this->soldiers.at(i)->play();
    // Play skelletons
    for (int i = 0; i < (int) this->skeletons.size(); i++)
        this->skeletons.at(i)->play();
    // Move player
    this->player->getSprite()->move(
        *this->player->getMovement() * dt.asSeconds());
    if (this->player->getAnimStop())
        this->player->stopAnimation();
    // Move soldiers
    for (int i = 0; i < (int) this->soldiers.size(); i++) {
        Vector2f direction = this->getDirectionToUnit(this->soldiers.at(i),
                                                      this->player);
        this->updateDirectionUnit(this->soldiers.at(i), direction);
        this->soldiers.at(i)->getSprite()->move(
            *this->soldiers.at(i)->getMovement() * dt.asSeconds());
    }
    // Move skeletons
    for (int i = 0; i < (int) this->skeletons.size(); i++) {
        Vector2f direction = this->getDirectionToUnit(this->skeletons.at(i),
                                                      this->player);
        this->updateDirectionUnit(this->skeletons.at(i), direction);
        this->skeletons.at(i)->getSprite()->move(
            *this->skeletons.at(i)->getMovement() * dt.asSeconds());
    }
    
    // Update player
    this->player->getSprite()->update(dt);
    // Update soldier
    for (int i = 0; i < (int) this->soldiers.size(); i++)
        this->soldiers.at(i)->getSprite()->update(dt);
    // Update skeletons
    for (int i = 0; i < (int) this->skeletons.size(); i++)
        this->skeletons.at(i)->getSprite()->update(dt);
    // Check bullets
    this->player->checkBullets(this->game->window.getSize());
    for (int i = 0; i < (int) this->player->bullets.size(); i++)
        this->player->bullets.at(i).update();

    // Test collisions
    this->testCollisions();
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
    for (int i = 0; i < (int) this->soldiers.size(); i++) {
        this->soldiers.at(i)->getMovement()->x = 0;
        this->soldiers.at(i)->getMovement()->y = 0;
    }
    for (int i = 0; i < (int) this->skeletons.size(); i++){
        this->skeletons.at(i)->getMovement()->x = 0;
        this->skeletons.at(i)->getMovement()->y = 0;
    }
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
        /*
          std::cout << "Position: x:"
          << this->player->getSprite()->getPosition().x
          << " y: " << this->player->getSprite()->getPosition().y
          << std::endl;
          std::cout << this->game->window.getSize().x << " "
          << this->game->window.getSize().y << std::endl;
        */
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

Vector2f GameStateLevel::getNextEnemyPos()
{
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, 3);
    std::uniform_int_distribution<std::mt19937::result_type> d0(438, 503);
    std::uniform_int_distribution<std::mt19937::result_type> d1(150, 305);
    std::uniform_int_distribution<std::mt19937::result_type> d2(409, 582);
    std::uniform_int_distribution<std::mt19937::result_type> d3(170, 302);
    switch ((int) dist(this->rng)) {
    case 0:
        return {(float) d0(this->rng), 25.f};
    case 1:
        return {845.f, (float) d1(this->rng)};
    case 2:
        return {(float) d2(this->rng), 410.f};
    case 3:
        return {140.f, (float) d3(this->rng)};
    default:
        return {this->game->window.getSize().x / 2.f,
                this->game->window.getSize().y / 2.f};
        break;
    }
}

void GameStateLevel::loadEnemy(int type, bool special)
{
    if (special)
        this->skeletons.push_back(new Skeleton(this->getNextEnemyPos()));
    else
        this->soldiers.push_back(new Soldier(this->getNextEnemyPos(), type));
}

Vector2f GameStateLevel::getDirectionToUnit(Unit *source, Unit *destination)
{
    return {destination->getPosition().x - source->getPosition().x,
            destination->getPosition().y - source->getPosition().y};
}

void GameStateLevel::updateDirectionUnit(Unit *unit, Vector2f &direction)
{
    if (direction.x < 0) {
        unit->changeAnimation(unit->getAnimationLeft());
        unit->getMovement()->x -= unit->getSpeed();
    } else {
        unit->changeAnimation(unit->getAnimationRight());
        unit->getMovement()->x += unit->getSpeed();
    }
    if (direction.y < 0) {
        unit->changeAnimation(unit->getAnimationUp());
        unit->getMovement()->y -= unit->getSpeed();
    } else {
        unit->changeAnimation(unit->getAnimationDown());
        unit->getMovement()->y += unit->getSpeed();
    }
}

void GameStateLevel::testCollisions()
{
    int del_bullet;
    vector<int> del_soldier;
    vector<int> del_skeleton;
    // Soldiers with bullets
    for (int i = 0; i < (int) this->soldiers.size(); i++) {
        int j = 0;
        bool found = false;
        int bulletsSize = (int) this->player->bullets.size();
        while (!found && j < bulletsSize) {
            if (isIntersecting(*this->soldiers.at(i),
                               this->player->bullets.at(j))) {
                del_soldier.push_back(i);
                del_bullet = j;
                found = true;
            } else {
                j++;
            }
        }
        if (found) {
            this->player->bullets.erase(
                this->player->bullets.begin() + del_bullet);
        }
    }
    // Delete soldiers & compute points
    for (int i = 0; i < (int) del_soldier.size(); i++) {
        this->updatePoints(this->soldiers.at(del_soldier.at(i))->getPoints());
        this->soldiers.erase(this->soldiers.begin() + del_soldier.at(i));
    }
    // Skeletons with bullets
    for (int i = 0; i < (int) this->skeletons.size(); i++) {
        int j = 0;
        bool found = false;
        int bulletsSize = (int) this->player->bullets.size();
        while (!found && j < bulletsSize) {
            if (isIntersecting(*this->skeletons.at(i),
                               this->player->bullets.at(j))) {
                del_bullet = j;
                del_skeleton.push_back(i);
                found = true;
            } else {
                j++;
            }
        }
        if (found) {
            this->player->bullets.erase(
                this->player->bullets.begin() + del_bullet);
        }
    }
    // Delete skeletons & compute points
    for (int i = 0; i < (int) del_skeleton.size(); i++) {
        this->updatePoints(this->skeletons.at(del_skeleton.at(i))->getPoints());
        this->skeletons.erase(this->skeletons.begin() + del_skeleton.at(i));
    }
    // Collisions with player
    bool gameover = false;
    int i = 0;
    while (!gameover && i < (int) this->soldiers.size()) {
        if (!isIntersecting(*this->soldiers.at(i), *this->player))
            i++;
        else
            gameover = true;
    }
    if (!gameover) {
        i = 0;
        while (!gameover && i < (int) this->skeletons.size()) {
            if (!isIntersecting(*this->skeletons.at(i), *this->player))
                i++;
            else
                gameover = true;
        }
    }
    if (gameover) {
        this->soldiers.clear();
        this->skeletons.clear();
        cout << "GAME OVER" << endl;
        // TODO properly delete player
    }
}

void GameStateLevel::updatePoints(int points)
{
    this->points += points;
}
