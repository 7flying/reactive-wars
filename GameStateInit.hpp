#ifndef GAME_STATE_INIT_HPP
#define GAME_STATE_INIT_HPP

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "GameState.hpp"
#include "GameStateLevel.hpp"


using namespace std;


class GameStateInit : public GameState {
private:
    View view;
    void newGame();
    void loadGame();
    void credits();

public:
    GameStateInit(Game *game);

    virtual void draw(const Time dt);
    virtual void update(const Time dt);
    virtual void handleInput();
};

#endif // GAME_STATE_INIT_HPP
