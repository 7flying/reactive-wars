#include "Soldier.hpp"


Soldier::Soldier(Vector2f initialPos, int variant):Unit(initialPos)
{
    this->variant = (variant < 0 || variant > 2) ? 0 : variant;
    switch(this->variant)
    {
    case 1:
        this->texture.loadFromFile("media/soldier2.png");
        this->baseSpeed = 50.f;
        this->speed = 50.f;
        break;
    case 2:
        this->texture.loadFromFile("media/soldier3.png");
        this->baseSpeed = 55.f;
        this->speed = 55.f;
        break;
    case 0: default:
        this->texture.loadFromFile("media/soldier.png");
        this->baseSpeed = 40.f;
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

Vector2f Soldier::getDesviation(mt19937 &rng)
{
    std::uniform_int_distribution<std::mt19937::result_type> d0(5, 35);
    std::uniform_int_distribution<std::mt19937::result_type> d1(5, 25);
    std::uniform_int_distribution<std::mt19937::result_type> d2(5, 20);
    switch (this->variant) {
    case 0:
        return {(float) d0(rng), (float) d0(rng)};
    case 1:
        return {(float) d1(rng), (float) d1(rng)};
    case 2:
        return {(float) d2(rng), (float) d2(rng)};
    default:
        return {(float) d0(rng), (float) d0(rng)};
        break;
    }
}

void Soldier::addDesviation(Vector2f &desviation, Vector2f *direction)
{
    if (direction->x < 0)
        this->getMovement()->x -= desviation.x;
    else
        this->getMovement()->x += desviation.x;
    if (direction->y < 0)
        this->getMovement()->y -= desviation.y;
    else
        this->getMovement()->y += desviation.y;
}
