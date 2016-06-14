#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <iostream> // just cout oriented testing
#include <math.h>
#include "Tile.hpp"
#include "PerlinNoise.hpp"


using namespace std;


class Map {
private:
    void depthfirstsearch(vector<TileType> &whiteList, Vector2i pos, int label,
                          int regType);

public:
    unsigned int width, height;
    vector<Tile> tiles;
    vector<int> resources;

    unsigned int tileSize, numSelected;
    unsigned int numRegions[1];

    // 0 deselected, 1 selected, 2 invalid
    vector<char> selected;

    Map();
    Map(const string &filename, unsigned int width, unsigned int height,
        map<string, Tile> &tileAtlas);


    /** Generates a map using Perlin Noise **/
    void proceduralMap(unsigned int width, unsigned int height,
                       map<std::string, Tile> &tileAtlas);
    /** Load map from disk **/
    void load(const string &filename, unsigned int width, unsigned int height,
              map<std::string, Tile> &tileAtlas);
    /** Save map to disk **/
    void save(const string &filename);
    /** Draw the map **/
    void draw(RenderWindow &window, float dt);
    /** Check if the position in the map is connected to another by only
      * traversing tiles in the whitelist **/
    void findConnectedRegions(vector<TileType> whitelist, int type);
    /** Update the direction of directional tiles so that they face the correct
      * way. Used to orient roads, pylos, rivers etc */
    void updateDirection(TileType tileType);
    /** Select the tiles within the bounds **/
    void select(Vector2i start, Vector2i end, vector<TileType> blacklist);
    /** Deselect all the tiles **/
    void clearSelected();
};

#endif // MAP_HPP
