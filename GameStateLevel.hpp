#ifndef GAME_STATE_LEVEL_HPP
#define GAME_STATE_LEVEL_HPP

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "GameState.hpp"

using namespace std;


class GameStateLevel : public GameState {

private:
    View view;

public:
    GameStateLevel(Game *game);

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();
};

#endif // GAME_STATE_LEVEL_HPP
