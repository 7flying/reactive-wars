#ifndef SOLDIER_HPP
#define SOLDIER_HPP

#include "Unit.hpp"

using namespace sf;


class Soldier: public Unit {
private:
    int variant;

public:
    Soldier(Vector2f initialPos, int variant);
    virtual Vector2f getSize();
    virtual int getPoints();
    int getVariant() { return this->variant; }
};

#endif // SOLDIER_HPP
