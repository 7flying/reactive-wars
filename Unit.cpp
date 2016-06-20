#include "Unit.hpp"


Unit::Unit(Vector2f initialPos)
{
    this->sprite = new AnimatedSprite(seconds(0.2), true, false);
    this->sprite->setPosition(initialPos);
}

Unit::~Unit()
{
    delete current;
    delete sprite;
    delete movement;
    std::cout << "Deleting unit" << std::endl;
}

void Unit::changeAnimation(SpriteAnimation *animation)
{
    this->current = animation;
}

void Unit::updateSpeed(float s)
{
    this->speed = s;
}


void Unit::stopAnimation()
{
    this->sprite->stop();
}

void Unit::play()
{
    this->sprite->play(*this->current);
}

void Unit::setSpeed(float speed)
{
    this->speed = speed;
}

void Unit::setAnimStop(bool stop)
{
    this->animStop = stop;
}

int Unit::getPoints()
{
    return 0;
}

Vector2f Unit::getSize()
{
    return {0.f, 0.f};
}
