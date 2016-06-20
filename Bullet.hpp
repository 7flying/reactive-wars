#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics.hpp>
#include "Game.hpp"

using namespace std;
using namespace sf;


class Bullet {
private:
    RectangleShape shape;
    Vector2f velocity{0.f, 0.f};

public:
    static constexpr float ABS_VELOCITY = 5.0f;
    static const int WIDTH = 2;
    static const int HEIGHT = 2;
    
    Bullet(float mx, float my, Vector2f velocity);
    void update();
    /* Checks if the bullet is outside the window */
    bool checkOutOfWindow(Vector2u window) const;
    RectangleShape *getShape() { return &this->shape; }

    /* Methods for collisions */
    float x() { return this->shape.getPosition().x; }
    float y() { return this->shape.getPosition().y; }
    float left() { return this->x() - this->shape.getSize().x / 2.f; }
    float right() { return this->x() + this->shape.getSize().x / 2.f; }
    float top() { return this->y() - this->shape.getSize().y / 2.f; }
    float bottom() { return this->y() + this->shape.getSize().y / 2.f; }
};

#endif // BULLET_HPP
