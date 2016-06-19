#include "Unit.hpp"


Unit::Unit(Vector2f initialPos)
{
    this->sprite = new AnimatedSprite(seconds(0.2), true, false);
    this->sprite->setPosition(initialPos);
}

void Unit::changeAnimation(SpriteAnimation *animation)
{
    this->current = animation;
}

void Unit::updateSpeed(float s)
{
    this->speed = s;
}

Vector2f Unit::getPosition()
{
    return this->sprite->getPosition();
}

SpriteAnimation *Unit::getAnimationUp()
{
    return &this->up;
}

SpriteAnimation *Unit::getAnimationDown()
{
    return &this->down;
}

SpriteAnimation *Unit::getAnimationLeft()
{
    return &this->left;
}

SpriteAnimation *Unit::getAnimationRight()
{
    return &this->right;
}

AnimatedSprite *Unit::getSprite()
{
    return this->sprite;
}

void Unit::stopAnimation()
{
    this->sprite->stop();
}

void Unit::play()
{
    this->sprite->play(*this->current);
}

float Unit::getSpeed()
{
    return this->speed;
}

void Unit::setSpeed(float speed)
{
    this->speed = speed;
}

Vector2f *Unit::getMovement()
{
    return this->movement;
}

bool Unit::getAnimStop()
{
    return this->animStop;
}

void Unit::setAnimStop(bool stop)
{
    this->animStop = stop;
}

int Unit::getPoints()
{
    return 0;
}
