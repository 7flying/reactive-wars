#ifndef UNIT_HPP
#define UNIT_HPP

#include <SFML/Graphics.hpp>
#include "SpriteAnimation.hpp"
#include "AnimatedSprite.hpp"

using namespace sf;


class Unit {

protected:
    SpriteAnimation up, down, left, right;
    SpriteAnimation *current;
    Texture texture;
    AnimatedSprite *sprite;
    float speed;
    Vector2f *movement;
    bool animStop = false;

public:
    Unit(Vector2f initialPos);
    /* Changes the animation */
    void changeAnimation(SpriteAnimation *animation);
    /* Updates the speed of the player **/
    void updateSpeed(float s);
    /** Gets the animations **/
    SpriteAnimation *getAnimationUp();
    SpriteAnimation *getAnimationDown();
    SpriteAnimation *getAnimationLeft();
    SpriteAnimation *getAnimationRight();
    /** Gets the sprite **/
    AnimatedSprite *getSprite();
    /** Stops playing the animation **/
    void stopAnimation();
    /** Plays the animation **/
    void play();
    /** Gets the player's speed **/
    float getSpeed();
    /** Sets the player's speed **/
    void setSpeed(float speed);
    /** Get movement **/
    Vector2f *getMovement();
    bool getAnimStop();
    void setAnimStop(bool stop);
};


#endif // UNIT_HPP
