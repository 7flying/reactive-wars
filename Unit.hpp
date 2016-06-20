#ifndef UNIT_HPP
#define UNIT_HPP

#include <vector>
#include <iostream>
#include <random>
#include <utility>
#include <SFML/Graphics.hpp>
#include "SpriteAnimation.hpp"
#include "AnimatedSprite.hpp"

using namespace std;
using namespace sf;


class Unit {

protected:
    SpriteAnimation an_up, an_down, an_left, an_right;
    SpriteAnimation *current;
    Texture texture;
    AnimatedSprite *sprite;
    float speed;
    Vector2f *movement;
    bool animStop = false;

public:
    Unit(Vector2f initialPos);
    virtual ~Unit();
    /* Changes the animation */
    void changeAnimation(SpriteAnimation *animation);
    /* Updates the speed of the player **/
    void updateSpeed(float s);
    /* Get position */
    Vector2f getPosition() { return this->sprite->getPosition(); }
    /** Gets the animations **/
    SpriteAnimation *getAnimationUp() { return &this->an_up; }
    SpriteAnimation *getAnimationDown() { return &this->an_down; }
    SpriteAnimation *getAnimationLeft() { return &this->an_left; }
    SpriteAnimation *getAnimationRight() { return &this->an_right; }
    /** Gets the sprite **/
    AnimatedSprite *getSprite(){ return this->sprite; }
    /** Stops playing the animation **/
    void stopAnimation();
    /** Plays the animation **/
    void play();
    /** Gets the player's speed **/
    float getSpeed(){ return this->speed; }
    /** Sets the player's speed **/
    void setSpeed(float speed);
    /** Get movement **/
    Vector2f *getMovement() { return this->movement; }
    bool getAnimStop() { return this->animStop; }
    void setAnimStop(bool stop);
    /** Get the points for defeating this unit **/
    virtual int getPoints();
    /** Gets the size of the sides of the sprite **/
    virtual Vector2f getSize();

    /** Methods for collisions **/
    float x() { return this->sprite->getPosition().x; }
    float y() { return this->sprite->getPosition().y; }
    float left() { return this->x() - this->getSize().x / 2.f; }
    float right() { return this->x() + this->getSize().x / 2.f; }
    float top() { return this->y() - this->getSize().y / 2.f; }
    float bottom() { return this->y() + this->getSize().y / 2.f; }
};


#endif // UNIT_HPP
