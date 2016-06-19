#include "Soldier.hpp"


Soldier::Soldier(Vector2f initialPos, int variant):Unit(initialPos)
{
    this->variant = (variant < 0 || variant > 2) ? 0 : variant;
    switch(this->variant)
    {
    case 1:
        this->texture.loadFromFile("media/soldier2.png");
        this->speed = 50.f;
        break;
    case 2:
        this->texture.loadFromFile("media/soldier3.png");
        this->speed = 70.f;
        break;
    case 0: default:
        this->texture.loadFromFile("media/soldier.png");
        this->speed = 40.f;
        break;
    }
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
}

int Soldier::getVariant()
{
    return this->variant;
}

int Soldier::getPoints()
{
    switch (this->variant) {
    case 0:
        return 40;
    case 1:
        return 50;
    case 2:
        return 70;
    default:
        return 0;
    }
}
