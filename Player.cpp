#include "Player.hpp"


Player::Player(Vector2f initialPos)
{
    this->texture.loadFromFile("media/arch.png");
    this->down.setSpriteSheet(texture);
    this->left.setSpriteSheet(texture);
    this->right.setSpriteSheet(texture);
    this->up.setSpriteSheet(texture);
    
    for (int i = 224; i > 0; i-=32) {
        this->down.addFrame(IntRect(i, 0, 32, 32));
        this->left.addFrame(IntRect(i, 32, 32, 32));
        this->right.addFrame(IntRect(i, 64, 32, 32));
        this->up.addFrame(IntRect(i, 96, 32, 32));
    }

    this->current = &this->up;
    this->sprite = new AnimatedSprite(seconds(0.2), true, false);
    this->sprite->setPosition(initialPos);
    this->movement = new Vector2f(0.f, 0.f);
    this->speed = 80.f;
}

void Player::changeAnimation(SpriteAnimation *animation)
{
    this->current = animation;
}

void Player::updateSpeed(float s)
{
    this->speed = s;
}

SpriteAnimation *Player::getAnimationUp()
{
    return &this->up;
}

SpriteAnimation *Player::getAnimationDown()
{
    return &this->down;
}

SpriteAnimation *Player::getAnimationLeft()
{
    return &this->left;
}

SpriteAnimation *Player::getAnimationRight()
{
    return &this->right;
}

AnimatedSprite *Player::getSprite()
{
    return this->sprite;
}

void Player::stopAnimation()
{
    this->sprite->stop();
}

void Player::play()
{
    this->sprite->play(*this->current);
}

float Player::getSpeed()
{
    return this->speed;
}

void Player::setSpeed(float speed)
{
    this->speed = speed;
}

Vector2f *Player::getMovement()
{
    return this->movement;
}

bool Player::getAnimStop()
{
    return this->animStop;
}

void Player::setAnimStop(bool stop)
{
    this->animStop = stop;
}
