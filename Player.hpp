#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "SpriteAnimation.hpp"
#include "AnimatedSprite.hpp"

using namespace sf;


class Player {

private:
    SpriteAnimation up, down, left, right;
    SpriteAnimation *current;
    Texture texture;
    AnimatedSprite *sprite;
    float speed;

public:
    Vector2f movement;
    Player(Vector2f initialPos);
    void changeAnimation(SpriteAnimation *animation);
    void updateSpeed(float s);
    SpriteAnimation* getAnimationUp();
    SpriteAnimation* getAnimationDown();
    SpriteAnimation* getAnimationLeft();
    SpriteAnimation* getAnimationRight();
    AnimatedSprite* getSprite();
    void stopAnimation();
    void play();
};


#endif // PLAYER_HPP
