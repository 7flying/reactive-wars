#include "Skeleton.hpp"


Skeleton::Skeleton(Vector2f initialPos):Unit(initialPos)
{
    this->texture.loadFromFile("media/skeleton.png");
    this->an_down.setSpriteSheet(texture);
    this->an_left.setSpriteSheet(texture);
    this->an_right.setSpriteSheet(texture);
    this->an_up.setSpriteSheet(texture);
    
    for (int i = 126; i > 0; i-= 18) {
        this->an_down.addFrame(IntRect(i, 0, 18, 20));
        this->an_left.addFrame(IntRect(i, 20, 18, 20));
        this->an_right.addFrame(IntRect(i, 40, 18, 20));
        this->an_up.addFrame(IntRect(i, 60, 18, 20));
    }

    this->current = &this->an_up;
    this->movement = new Vector2f(0.f, 0.f);
    this->speed = 60.f;
    this->baseSpeed = 60.f;
}

int Skeleton::getPoints()
{
    return 60;
}

Vector2f Skeleton::getSize()
{
    return {18.f, 20.f};
}
