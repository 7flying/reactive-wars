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
        this->speed = 55.f;
        break;
    case 0: default:
        this->texture.loadFromFile("media/soldier.png");
        this->speed = 40.f;
        break;
    }
    this->an_down.setSpriteSheet(texture);
    this->an_left.setSpriteSheet(texture);
    this->an_right.setSpriteSheet(texture);
    this->an_up.setSpriteSheet(texture);
    for (int i = 224; i > 0; i-= 32) {
        this->an_down.addFrame(IntRect(i, 0, 32, 32));
        this->an_left.addFrame(IntRect(i, 32, 32, 32));
        this->an_right.addFrame(IntRect(i, 64, 32, 32));
        this->an_up.addFrame(IntRect(i, 96, 32, 32));
    }

    this->current = &this->an_up;
    this->movement = new Vector2f(0.f, 0.f);
}

Soldier::~Soldier()
{
    std::cout << "Deleting soldier" << std::endl;
}

Vector2f Soldier::getSize()
{
    return {32.f, 32.f};
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
