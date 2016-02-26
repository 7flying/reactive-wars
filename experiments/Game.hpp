#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <stack>
#include <map>
#include "TextureManager.hpp"
#include "Tile.hpp"

using namespace std;
using namespace sf;

// Avoid circular includes declaring GameState here.
class GameState;

class Game
{
private:
    void loadTextures();
    void loadTiles();

public:

    Game();
    ~Game();

    /* Store the game states **/
    stack<GameState*> states;
    /** Main game window **/
    RenderWindow window;
    /** Texture manager **/
    TextureManager texman;
    /** Background image **/
    Sprite background;

    const static int tileSize = 8;
    map<string, Tile> tileAtlas;

    /* Pushes a state into the game state stack.*/
    void pushState(GameState *state);
    /* Removes the top state from the stack.*/
    void popState();
    /* Pops the previous state if present and pushes the new one.*/
    void changeState(GameState *state);
    /* Returns a pointer to the state at the top of the stack.*/
    GameState* peekState();
    /* Main.*/
    void gameLoop();
};

#endif // GAME_HPP
