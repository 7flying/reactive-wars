#ifndef GAME_STATE_EDITOR_HPP
#define GAME_STATE_EDITOR_HPP

#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "Map.hpp"


enum class ActionState { NONE, PANNING };

class GameStateEditor : public GameState
{
private:
    ActionState actionState;
    View gameView;
    View guiView;
    Map map;
    Vector2i panningAnchor;
    float zoomLevel;

public:

    GameStateEditor(Game *game);
    
    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();
};

#endif // GAME_STATE_EDITOR_HPP
