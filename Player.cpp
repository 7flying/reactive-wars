#include "Player.hpp"


Player::Player(Vector2f initialPos):Unit(initialPos)
{
    this->texture.loadFromFile("media/arch.png");
    this->an_down.setSpriteSheet(texture);
    this->an_left.setSpriteSheet(texture);
    this->an_right.setSpriteSheet(texture);
    this->an_up.setSpriteSheet(texture);
    
    for (int i = 224; i > 0; i-= 32) {
        this->an_down.addFrame(IntRect(i, 0, 32, 32));
        this->an_left.addFrame(IntRect(i, 32, 32, 32));
        this->an_right.addFrame(IntRect(i, 64, 32, 32));
        this->an_up.addFrame(IntRect(i, 96, 32, 32));
    }

    this->current = &this->an_up;
    this->movement = new Vector2f(0.f, 0.f);
    this->speed = 80.f;
}

Vector2f Player::getSize()
{
    return {32.f, 32.f};
}

void Player::fireBullet(Vector2i direction)
{
    this->bullets.push_back(Bullet(
                                this->sprite->getPosition().x + SIDE_SIZE * 0.5,
                                this->sprite->getPosition().y + SIDE_SIZE * 0.5,
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
    for (int i = 0; i < (int) toDelete.size(); i++)
        this->bullets.erase(this->bullets.begin() + toDelete.at(i));
}
