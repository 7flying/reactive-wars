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
    RectangleShape *getShape();
};


#endif // BULLET_HPP
