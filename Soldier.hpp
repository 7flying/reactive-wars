#ifndef SOLDIER_HPP
#define SOLDIER_HPP

#include "Unit.hpp"

using namespace sf;


class Soldier: public Unit {
private:
    int variant;

public:
    Soldier(Vector2f initialPos, int variant);
    int getVariant();
    virtual int getPoints();
};

#endif // SOLDIER_HPP
