#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <stack>
#include <map>

using namespace std;
using namespace sf;


class GameState;

class Game {

private:

    /* Loads the required fonts for the game.*/
    void loadFonts();

public:
    Game();
    ~Game();

    // Stack to store the different states of the game
    stack<GameState*> states;
    // Main game window
    RenderWindow window;

    // -- Assets --
    map<string, Font> fonts;
    
};

#endif // GAME_HPP
