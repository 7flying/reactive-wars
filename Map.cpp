#include "Map.hpp"

using namespace std;


Map::Map() {
    this->numSelected = 0;
    this->tileSize = 8;
    this->width = 0;
    this->height = 0;
    this->numRegions[0] = 1;
}
    
Map::Map(const string &filename, unsigned int width, unsigned int height,
         map<string, Tile> &tileAtlas)
{
    this->numSelected = 0;
    this->tileSize = 8;
    this->width = width;
    this->height = height;
    proceduralMap(width, height, tileAtlas);

    this->units.clear();
    this->units.push_back(tileAtlas.at("red-soldier"));
}

void Map::proceduralMap(int width, int height, map<string, Tile> &tileAtlas)
{
    this->width = width;
    this->height = height;
    this->tiles.clear();
    // PerlinNoise pnoise;
    // Generate array for perlin noise
    float ** a_pnoise = new float*[height];
    for (int i = 0; i < height; i++)
        a_pnoise[i] = new float[width];
    this->pnoise.generatePerlinNoise(width, height, 5, 0.7f, a_pnoise); // 5, 0.7 | 5, 0.3
    // Map each value to a tile type
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            this->resources.push_back(255);
            this->selected.push_back(0);
            double sec = round(a_pnoise[i][j] * (TILE_NUM - 1));
            if (std::isinf(std::abs(sec)) || std::isnan(std::abs(sec))) {
                // get an adjacent tile
                if (i > 0 && j > 0)
                    sec = round(std::abs(a_pnoise[i-1][j-1] * (TILE_NUM -1)));
                else
                    sec = 0.0f;
            }
            if (sec < 0)
                sec *= -1;
            if (sec > (TILE_NUM - 1))
                sec = ((int) sec % TILE_NUM);
            if (sec < 0 || sec > (TILE_NUM - 1)) {
                std::cout << j << ", " << i << ": " << sec << " to ";
                sec = sec / (TILE_NUM - 1);
                std::cout << sec << std::endl;
            }
            switch((int) sec) {
            case 0:
                this->tiles.push_back(tileAtlas.at("grass"));
                break;
            case 1:
                this->tiles.push_back(tileAtlas.at("grass1"));
                break;
            case 2:
                this->tiles.push_back(tileAtlas.at("grass2"));
                break;
            case 3:
                this->tiles.push_back(tileAtlas.at("grass3"));
                break;
            case 4:
                this->tiles.push_back(tileAtlas.at("moun"));
                break;
            case 5:
                this->tiles.push_back(tileAtlas.at("moun1"));
                break;
            case 6:
                this->tiles.push_back(tileAtlas.at("water"));
                break;
            case 7:
                this->tiles.push_back(tileAtlas.at("water1"));
                break;
            case 8:
                this->tiles.push_back(tileAtlas.at("water2"));
                break;
            default:
                int temp = pnoise.randomValue(4, 5);
                if (temp == 4)
                    this->tiles.push_back(tileAtlas.at("moun"));
                else
                    this->tiles.push_back(tileAtlas.at("moun1"));
                break;
            }
        }
        Tile &tile = this->tiles.back();
        tile.avoid = 0;
        tile.defence = 0;
        tile.tileVariant = 1;
        tile.regions[0] = 0;
        tile.movement = 1;
    }

    // Clean array
    for (int i = 0; i < height; i++)
        delete[] a_pnoise[i];
    delete[] a_pnoise;

}

void Map::load(const string &filename, unsigned int width, unsigned int height,
               map<std::string, Tile> &tileAtlas)
{
}

void Map::save(const string &filename)
{
}

void Map::draw(RenderWindow &window, float dt)
{
    for (int y = 0; y < (int) this->height; y++) {
        for (int x = 0; x < (int) this->width; x++) {
            // Set the position of the tile in the 2d world
            Vector2f pos;
            pos.x = (x - y) * this->tileSize + this->width * this->tileSize;
            pos.y = (x + y) * this->tileSize * 0.5;
            this->tiles[y * this->width + x].sprite.setPosition(pos);
            // Change the color if the tile is selected
            if (this->selected[y * this->width + x])
                this->tiles[y * this->width + x].sprite.setColor(
                    Color(0x7d, 0x7d, 0x7d));
            else
                this->tiles[y * this->width + x].sprite.setColor(
                    Color(0xff, 0xff, 0xff));
            // Draw the tile
            this->tiles[y * this->width + x].draw(window, dt);
        }
    }
    Vector2f pos;
    //std::cout << "width: " << this->width << " tileSize " << this->tileSize << std::endl;
    pos.x = this->width * this->tileSize +  (this->tileSize * 0.5);
    pos.y = -8;
    this->units[0].sprite.setPosition(pos);
    //this->units[0].sprite.setColor(Color(0xff, 0xff, 0xff));
    this->units[0].draw(window, dt);
}

void Map::updateDirection(TileType tileType)
{
    for (int y = 0; y < (int) this->height; y++) {
        for (int x = 0; x < (int) this->width; x++) {
            int pos = y * this->width + x;
            if (this->tiles[pos].tileType != tileType)
                continue;
            bool adjacentTiles[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
            /* Check for adjacent tiles of the same type */
            if (x > 0 && y > 0)
                adjacentTiles[0][0] = (
                    this->tiles[(y-1) * this->width + (x - 1)].tileType == tileType);
            if (y > 0)
                adjacentTiles[0][1] = (
                    this->tiles[(y - 1) * this->width + (x)].tileType == tileType);
            if (x < (int) this->width-1 && y > 0)
                adjacentTiles[0][2] = (
                    this->tiles[(y - 1) * this->width + (x + 1)].tileType == tileType);
            if (x > 0)
                adjacentTiles[1][0] = (
                    this->tiles[(y) * this->width + (x - 1)].tileType == tileType);
            if (x < (int) width - 1)
                adjacentTiles[1][2] = (
                    this->tiles[(y) * this-> width + (x + 1)].tileType == tileType);
            if (x > 0 && y < (int) this-> height - 1)
                adjacentTiles[2][0] = (
                    this->tiles[(y + 1) * this->width + (x - 1)].tileType == tileType);
            if (y < (int) this->height - 1)
                adjacentTiles[2][1] = (
                    this->tiles[(y + 1) * this->width + (x)].tileType == tileType);
            if (x < (int) this->width - 1 && y < (int) this->height - 1)
                adjacentTiles[2][2] = (
                    this->tiles[(y + 1) * this->width + (x + 1)].tileType == tileType);

            /* Change the tile variant depending on the tile position */
            if (adjacentTiles[1][0] && adjacentTiles[1][2] &&
                adjacentTiles[0][1] && adjacentTiles[2][1])
                this->tiles[pos].tileVariant = 2;
            else if (adjacentTiles[1][0] && adjacentTiles[1][2] &&
                     adjacentTiles[0][1])
                this->tiles[pos].tileVariant = 7;
            else if (adjacentTiles[1][0] && adjacentTiles[1][2] &&
                     adjacentTiles[2][1])
                this->tiles[pos].tileVariant = 8;
            else if (adjacentTiles[0][1] && adjacentTiles[2][1] &&
                     adjacentTiles[1][0])
                this->tiles[pos].tileVariant = 9;
            else if (adjacentTiles[0][1] && adjacentTiles[2][1] &&
                     adjacentTiles[1][2])
                this->tiles[pos].tileVariant = 10;
            else if (adjacentTiles[1][0] && adjacentTiles[1][2])
                this->tiles[pos].tileVariant = 0;
            else if (adjacentTiles[0][1] && adjacentTiles[2][1])
                this->tiles[pos].tileVariant = 1;
            else if (adjacentTiles[2][1] && adjacentTiles[1][0])
                this->tiles[pos].tileVariant = 3;
            else if (adjacentTiles[0][1] && adjacentTiles[1][2])
                this->tiles[pos].tileVariant = 4;
            else if (adjacentTiles[1][0] && adjacentTiles[0][1])
                this->tiles[pos].tileVariant = 5;
            else if (adjacentTiles[2][1] && adjacentTiles[1][2])
                this->tiles[pos].tileVariant = 6;
            else if (adjacentTiles[1][0])
                this->tiles[pos].tileVariant = 0;
            else if (adjacentTiles[1][2])
                this->tiles[pos].tileVariant = 0;
            else if (adjacentTiles[0][1])    
                this->tiles[pos].tileVariant = 1;
            else if (adjacentTiles[2][1])
                this->tiles[pos].tileVariant = 1;
        }
    }
}

void Map::depthfirstsearch(vector<TileType> &whiteList, Vector2i pos, int label,
                           int regType=0)
{
    if (pos.x < 0 || pos.x >= (int) this->width || pos.y < 0 ||
        pos.y >= (int) this->height)
        return;
    if (this->tiles[pos.y * this->width + pos.x].regions[regType] != 0)
        return;
    bool found = false;
    for (auto type : whiteList) {
        if (type == this->tiles[pos.y * this->width + pos.x].tileType) {
            found = true;
            break;
        }
    }
    if (!found)
        return;
    this->tiles[pos.y * this->width + pos.x].regions[regType] = label;

    depthfirstsearch(whiteList, pos + Vector2i(-1, 0), label, regType);
    depthfirstsearch(whiteList, pos + Vector2i(0, 1), label, regType);
    depthfirstsearch(whiteList, pos + Vector2i(1, 0), label, regType);
    depthfirstsearch(whiteList, pos + Vector2i(0, -1), label, regType);
}

void Map::findConnectedRegions(vector<TileType> whitelist, int regType=0)
{
    int regions = 1;
    for(auto &tile : this->tiles)
        tile.regions[regType] = 0;
    for (int y = 0; y < (int) this->height; y++) {
        for (int x = 0; x < (int) this->width; x++) {
            bool found = false;
            for (auto type : whitelist) {
                if (type == this->tiles[y * this->width + x].tileType) {
                    found = true;
                    break;
                }
            }
            if (this->tiles[y * this->width + x].regions[regType] == 0 &&
                found)
            {
                depthfirstsearch(whitelist, Vector2i(x, y), regions++, regType);
            }
        }
    }
    this->numRegions[regType] = regions; 
}

void Map::clearSelected()
{
    for (auto &tile : this->selected)
        tile = 0;
    this->numSelected = 0;
}

void Map::select(Vector2i start, Vector2i end, vector<TileType> blacklist)
{
    // Swap coordinates if necessary
    if (end.y < start.y)
        swap(start.y, end.y);
    if (end.x < start.x)
        swap(start.x, end.x);
    //Clamp in range
    if ((unsigned) end.x >= this->width)
        end.x = this->width - 1;
    else if (end.x < 0)
        end.x = 0;
    if ((unsigned) end.y >= this->height)
        end.y = this->height - 1;
    else if(end.y < 0)
        end.y = 0;
    if ((unsigned) start.x >= this->width)
        start.x = this->width - 1;
    else if(start.x < 0)
        start.x = 0;
    if ((unsigned) start.y >= this->height)
        start.y = this->height - 1;
    else if(start.y < 0)
        start.y = 0;

    for (int y = start.y; y <= end.y; y++) {
        for (int x = start.x; x <= end.x; x++) {
            // Check if the tile type is in the blacklist. If it is mark it as
            // invalidad, otherwise select it
            this->selected[y * this->width + x] = 1;
            ++this->numSelected;
            for (auto type : blacklist) {
                if (this->tiles[y * this->width + x].tileType == type) {
                    this->selected[y * this->width + x] = 2;
                    --this->numSelected;
                    break;
                }
            }
        }
    }
}
