#ifndef GAME_STATE_START_HPP
#define GAME_STATE_START_HPP

#include <SFML/Graphics.hpp>
#include "GameState.hpp"

class GameStateStart : public GameState
{
private:
    View view;
    void loadgame();

public:

    GameStateStart(Game *game);
    
    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();
};

#endif // GAME_STATE_START_HPP
