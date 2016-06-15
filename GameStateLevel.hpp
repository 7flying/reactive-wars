#ifndef GAME_STATE_LEVEL_HPP
#define GAME_STATE_LEVEL_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Game.hpp"
#include "GameState.hpp"
#include "Map.hpp"


using namespace std;


enum class ActionState {NONE, PANNING};

class GameStateLevel : public GameState {

private:
    View gameView;
    View guiView;
    Map map;

    int x = 0;
    int y = 0;

    // To know what the user is doing
    ActionState actionState;
    // Records the mouse position
    Vector2i panningAnchor;
    // Gets the zoom (power of 2)
    float zoomLevel;

public:
    GameStateLevel(Game *game);

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();
};

#endif // GAME_STATE_LEVEL_HPP
