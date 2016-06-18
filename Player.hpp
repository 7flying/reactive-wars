#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Unit.hpp"

using namespace sf;


class Player: public Unit {

public:
    Player(Vector2f initialPos);
};


#endif // PLAYER_HPP
