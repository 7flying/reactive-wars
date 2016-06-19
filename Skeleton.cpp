#include "Skeleton.hpp"


Skeleton::Skeleton(Vector2f initialPos):Unit(initialPos)
{
    this->texture.loadFromFile("media/skeleton.png");
    this->down.setSpriteSheet(texture);
    this->left.setSpriteSheet(texture);
    this->right.setSpriteSheet(texture);
    this->up.setSpriteSheet(texture);
    
    for (int i = 126; i > 0; i-= 18) {
        this->down.addFrame(IntRect(i, 0, 18, 20));
        this->left.addFrame(IntRect(i, 20, 18, 20));
        this->right.addFrame(IntRect(i, 40, 18, 20));
        this->up.addFrame(IntRect(i, 60, 18, 20));
    }

    this->current = &this->up;
    this->movement = new Vector2f(0.f, 0.f);
    this->speed = 60.f;
}

int Skeleton::getPoints()
{
    return 60;
}
