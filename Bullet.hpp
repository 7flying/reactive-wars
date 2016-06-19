#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics.hpp>
#include "Game.hpp"

using namespace std;
using namespace sf;


class Bullet {
private:
    RectangleShape shape;
    Vector2f velocity{10.f, 10.f};
    

public:
    static constexpr float ABS_VELOCITY = 10.0f;
    static const int WIDTH = 10;
    static const int HEIGHT = 10;
    
    Bullet(float mx, float my, Vector2f origin, Vector2f velocity);
    void update();
    /* Checks if the bullet is outside the window */
    bool checkOutOfWindow(Vector2i window) const;
};


#endif // BULLET_HPP
