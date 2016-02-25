#ifndef GAME_STATE_EDITOR_HPP
#define GAME_STATE_EDITOR_HPP

#include <SFML/Graphics.hpp>
#include "GameState.hpp"

class GameStateEditor : public GameState
{
private:
    View gameView;
    View guiView;

public:

    GameStateEditor(Game *game);
    
    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();
};

#endif // GAME_STATE_EDITOR_HPP
