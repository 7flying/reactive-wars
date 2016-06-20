#ifndef GAME_STATE_LEVEL_HPP
#define GAME_STATE_LEVEL_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <random>
#include <iostream>
#include <utility>
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
    mt19937 rng;

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
    void loadEnemy(int type, bool special=false);
    Vector2f getDirectionToUnit(Unit *source, Unit *destination);
    void updateDirectionUnit(Unit *unit, Vector2f &direction);
    void testCollisions();

public:
    GameStateLevel(Game *game);

    virtual void draw(const Time dt);
    virtual void update(const Time dt);
    virtual void handleInput();
    void updatePoints(int points);
    long long getPoints() { return this->points; };
};

#endif // GAME_STATE_LEVEL_HPP
