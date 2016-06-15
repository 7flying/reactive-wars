#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <stack>
#include <map>
#include "TextureManager.hpp"
#include "FontManager.hpp"
#include "Tile.hpp"


using namespace std;
using namespace sf;


class GameState;

class Game {

private:

    /* Loads the required fonts for the game.*/
    void loadFonts();
    /* Loads the required textures.*/
    void loadTextures();
    /* Loads Tiles */
    void loadTiles();

public:
    Game();
    ~Game();

    // Stack to store the different states of the game
    stack<GameState*> states;
    // Main game window
    RenderWindow window;

    // -- Managers --
    TextureManager texman;
    FontManager fontman;

    // -- Assets --
    Sprite background;

    // -- Map Tiles --
    const static int tileSize = 8;
    map<string, Tile> tileAtlas;

    // -- Unit Tiles --
    const static int unitTileSize = 8;

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
