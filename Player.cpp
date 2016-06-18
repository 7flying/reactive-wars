#include "Player.hpp"


Player::Player(Vector2f initialPos):Unit(initialPos)
{
    this->texture.loadFromFile("media/arch.png");
    this->down.setSpriteSheet(texture);
    this->left.setSpriteSheet(texture);
    this->right.setSpriteSheet(texture);
    this->up.setSpriteSheet(texture);
    
    for (int i = 224; i > 0; i-= 32) {
        this->down.addFrame(IntRect(i, 0, 32, 32));
        this->left.addFrame(IntRect(i, 32, 32, 32));
        this->right.addFrame(IntRect(i, 64, 32, 32));
        this->up.addFrame(IntRect(i, 96, 32, 32));
    }

    this->current = &this->up;
    this->movement = new Vector2f(0.f, 0.f);
    this->speed = 80.f;
}


