#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include "Map.hpp"
#include "Tile.hpp"

using namespace std;


Map::Map() {
    this->tileSize = 8;
    this->width = 0;
    this->height = 0;
    this->numRegions[0] = 1;
}
    
Map::Map(const string &filename, unsigned int width, unsigned int height,
    map<string, Tile> &tileAtlas)
{
    this->tileSize;
    load(filename, width, height, tileAtlas);
}

void Map::load(const string &filename, unsigned int width, unsigned int height,
               map<std::string, Tile> &tileAtlas)
{
    ifstream inputFile;
    inputFile.open(filename, ios::in | ios::binary);
    this->width = width;
    this->height = height;

    for (int pos = 0; pos < this->width * this->height; pos++) {
        TileType tileType;
        inputFile.read((char*) &tileType, sizeof(int));
        switch(tileType)
        {
        default:
        case TileType::VOID:
        case TileType::GRASS:
            this->tiles.push_back(tileAtlas.at("grass"));
            break;
        case TileType::FOREST:
            this->tiles.push_back(tileAtlas.at("forest"));
            break;
        case TileType::WATER:
            this->tiles.push_back(tileAtlas.at("water"));
            break;
        case TileType::RESIDENTIAL:
            this->tiles.push_back(tileAtlas.at("residential"));
            break;
        case TileType::COMMERCIAL:
            this->tiles.push_back(tileAtlas.at("commercial"));
            break;
        case TileType::INDUSTRIAL:
            this->tiles.push_back(tileAtlas.at("industrial"));
            break;
        case TileType::ROAD:
            this->tiles.push_back(tileAtlas.at("road"));
            break;
        }
        Tile &tile = this->tiles.back();
        inputFile.read((char*) &tile.tileVariant, sizeof(int));
        inputFile.read((char*) &tile.regions, sizeof(int)*1); // ein?
        inputFile.read((char*) &tile.population, sizeof(double));
        inputFile.read((char*) &tile.storedGoods, sizeof(float));
    }
    inputFile.close();
}
