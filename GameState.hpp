#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "Game.hpp"


/* Base class for all the game states. */
class GameState {
    
public:
    Game *game;

    /** Draw state to the screen.**/
    virtual void draw(const float dt) = 0;
    /** Update the logic.**/
    virtual void update(const float dt) = 0;
    /** Handle user input.**/
    virtual void handleInput() = 0;
};

#endif // GAME_STATE_HPP
