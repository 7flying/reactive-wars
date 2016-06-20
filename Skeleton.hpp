#ifndef SKELETON_HPP
#define SKELETON_HPP

#include "Unit.hpp"

using namespace sf;


class Skeleton: public Unit {

public:
    Skeleton(Vector2f initialPos);
    virtual int getPoints();
    virtual Vector2f getSize();
    bool del = false;
};

#endif // SKELETON_HPP
