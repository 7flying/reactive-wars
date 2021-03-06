#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Unit.hpp"
#include "Bullet.hpp"
#include <iostream>

using namespace sf;


class Player: public Unit {
private:

    static const int SIDE_SIZE = 32;
    /** Gets the direction of the sprite (positive or negative) **/
    Vector2i getDirection();

public:
    vector<Bullet> bullets;
    Player(Vector2f initialPos);
    virtual ~Player();
    virtual Vector2f getSize();
    /** Checks if bullets have to be deleted **/
    void checkBullets(Vector2u window);
    /** Fires a bullet **/
    void fireBullet(Vector2i direction);
};

#endif // PLAYER_HPP
