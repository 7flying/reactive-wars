#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "AnimationHandler.hpp"

#define TILE_NUM 9

using namespace std;

enum class TileType {
    VOID, GRASS, GRASS1, GRASS2, GRASS3, MOUNTAIN, MOUNTAIN1, WATER, WATER1,
        WATER2,
    // unused:
        FOREST, RESIDENTIAL, COMMERCIAL, INDUSTRIAL, ROAD};

string tileTypeToStr(TileType type);

class Tile {
public:
    AnimationHandler animHandler;
    Sprite sprite;
    TileType tileType;
    // This allows different looking versions of the same tile
    int tileVariant;
    /** Region IDs of the tile, tiles in the same region are connected**/
    // TODO: first is for transport?
    unsigned int regions[1];
    unsigned int cost;

    // TODO: --- delete ---
    double population;
    unsigned int maxPopPerLevel;
    unsigned int maxLevels;
    float production;
    float storedGoods;
    // --- end delete --
    
    // Modificator to the characters defence, avoid and movement
    int defence, avoid, movement;

    Tile();
    Tile(const unsigned int tileSize, const unsigned int height,
         Texture &texture, const vector<Animation> &animations,
         const TileType tileType, const unsigned int cost,
         const unsigned int maxPopPerLevel, const unsigned int maxLevels);

    void draw(RenderWindow &window, float dt);
    void update();
    string getCost() { return to_string(this->cost); }
};

#endif // TILE_HPP
