#ifndef SOLDIER_HPP
#define SOLDIER_HPP

#include "Unit.hpp"

using namespace sf;


class Soldier: public Unit {
private:
    int variant;

public:
    Soldier(Vector2f initialPos, int variant);
    virtual ~Soldier();
    virtual Vector2f getSize();
    virtual int getPoints();
    int getVariant() { return this->variant; }
    Vector2f getDesviation(mt19937 &rng);
    void addDesviation(Vector2f &desviation,  Vector2f *direction);
    bool del = false;
};

#endif // SOLDIER_HPP
