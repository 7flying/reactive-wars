#include "Bullet.hpp"


Bullet::Bullet(float mx, float my, Vector2f velocity)
{
    this->shape.setPosition(mx, my);
    this->velocity.x = velocity.x;
    this->velocity.y = velocity.y;
    this->shape.setSize({Bullet::WIDTH, Bullet::HEIGHT});
    this->shape.setFillColor(Color::Black);
    this->shape.setOrigin(Bullet::WIDTH / 2.f, Bullet::HEIGHT / 2.f);
}

void Bullet::update()
{
    this->shape.move(this->velocity);
}

bool Bullet::checkOutOfWindow(Vector2u window) const
{
    if (this->shape.getPosition().x > window.x
        || this->shape.getPosition().x < 0)
        return true;
    if (this->shape.getPosition().y > window.y
        || this->shape.getPosition().y < 0)
        return true;
    return false;
}
