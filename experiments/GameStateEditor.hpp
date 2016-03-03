#ifndef GAME_STATE_EDITOR_HPP
#define GAME_STATE_EDITOR_HPP

#include <SFML/Graphics.hpp>
#include "GameState.hpp"
#include "Map.hpp"
#include "City.hpp"
#include "Gui.hpp"

enum class ActionState { NONE, PANNING, SELECTING };

class GameStateEditor : public GameState
{
private:
    ActionState actionState;
    View gameView;
    View guiView;
    //Map map;
    City city;
    Vector2i panningAnchor;
    float zoomLevel;

    Vector2i selectionStart, selectionEnd;
    Tile *currentTile;
    map<string, Gui> guiSystem;

public:

    GameStateEditor(Game *game);
    
    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();
};

#endif // GAME_STATE_EDITOR_HPP
