#include "Player.hpp"


Player::Player(Vector2f initialPos):Unit(initialPos)
{
    this->texture.loadFromFile("media/arch.png");
    this->down.setSpriteSheet(texture);
    this->left.setSpriteSheet(texture);
    this->right.setSpriteSheet(texture);
    this->up.setSpriteSheet(texture);
    
    for (int i = 224; i > 0; i-= 32) {
        this->down.addFrame(IntRect(i, 0, 32, 32));
        this->left.addFrame(IntRect(i, 32, 32, 32));
        this->right.addFrame(IntRect(i, 64, 32, 32));
        this->up.addFrame(IntRect(i, 96, 32, 32));
    }

    this->current = &this->up;
    this->movement = new Vector2f(0.f, 0.f);
    this->speed = 80.f;
}


void Player::fireBullet(Vector2i direction)
{
    std::cout << "Firing: Position: " << this->sprite->getPosition().x
              << ", " << this->sprite->getPosition().y << " origin (same), velocity: "
              << (direction.x * Bullet::ABS_VELOCITY) << ", "
              << (direction.y * Bullet::ABS_VELOCITY) << std::endl;
    this->bullets.push_back(Bullet(this->sprite->getPosition().x,
                                   this->sprite->getPosition().y,
                                   {Bullet::ABS_VELOCITY * direction.x,
                                           Bullet::ABS_VELOCITY * direction.y}));
}

Vector2i Player::getDirection()
{
    int x = 1, y = 1;
    if (this->sprite->getPosition().x < 0)
        x = -1;
    if (this->sprite->getPosition().y < 0)
        y = -1;
    return {x, y};
}

void Player::checkBullets(Vector2u window)
{
    vector<int> toDelete;
    for (int i = 0; i < (int) this->bullets.size(); i++) {
        bool status = this->bullets.at(i).checkOutOfWindow(window);
        if (status)
            toDelete.push_back(i);
    }
    for (int i = 0; i < (int) toDelete.size(); i++) {
        this->bullets.erase(this->bullets.begin() + toDelete.at(i));
        cout << "Erasing element: " << i << endl;
    }
}
