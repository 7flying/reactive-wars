#ifndef GAME_STATE_LEVEL_HPP
#define GAME_STATE_LEVEL_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <random>
#include <iostream>
#include <utility>
#include <math.h>
#include "Game.hpp"
#include "GameState.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Skeleton.hpp"
#include "Soldier.hpp"
#include "Collisions.hpp"


using namespace std;


enum class ActionState {NONE, PANNING};

class GameStateLevel : public GameState {

private:
    View gameView;
    View guiView;
    Map map;
    long long points;
    unsigned int level;
    bool mapLoaded = false;
    bool gameOver = false;
    mt19937 rng;

    Font *guiFont;
    const static int FONT_SIZE_PIXELS = 8;
    const static int MED_FONT_SIZE_PIXELS = FONT_SIZE_PIXELS * 4;
    const static int LAR_FONT_SIZE_PIXELS = MED_FONT_SIZE_PIXELS * 2;
    string sPoints = "Points: ";
    string sLevel = "Level: ";
    string sGameOver = "Game Over";
    Text *textPoints;
    Text *textLevel;
    Text *textGameOver;

    int x = 0;
    int y = 0;

    // To know what the user is doing
    ActionState actionState;
    // Records the mouse position
    Vector2i panningAnchor;
    // Gets the zoom (power of 2)
    float zoomLevel;

    // Player
    Player *player;
    // Normal enemies
    vector<Soldier*> soldiers;
    // Special enemies
    vector<Skeleton*> skeletons;

    Vector2f getNextEnemyPos();
    void generateEnemies();
    void loadEnemy(int type, bool special=false);
    Vector2f getDirectionToUnit(Unit *source, Unit *destination);
    void updateDirectionUnit(Unit *unit, Vector2f &direction);
    void testCollisions(const Time dt);
    void levelUp();
    void changeSpeedByPos(Unit *unit);
public:
    GameStateLevel(Game *game);

    virtual void draw(const Time dt);
    virtual void update(const Time dt);
    virtual void handleInput();
    void updatePoints(int points);
    long long getPoints() { return this->points; };
};

#endif // GAME_STATE_LEVEL_HPP
