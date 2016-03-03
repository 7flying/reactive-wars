#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "City.hpp"
#include "Tile.hpp"


City::City()
{
    this->birthRate = 0.00055;
    this->deathRate = 0.00023;
    this->propCanWork = 0.50;
    this->populationPool = 0;
    this->population = populationPool;
    this->employmentPool = 0;
    this->employable = employmentPool;
    this->residentialTax = 0.05;
    this->commercialTax = 0.05;
    this->industrialTax = 0.05;
    this->earnings = 0;
    this->funds = 0;
    this->currentTime = 0.0;
    this->timePerDay = 1.0;
    this->day = 0;
}

City::City(string cityName, int tileSize,
           std::map<string, Tile> &tileAtlas) : City()
{
    this->map.tileSize = tileSize;
    this->load(cityName, tileAtlas);
}

double City::distributePool(double &pool, Tile &tile, double rate = 0.0)
{
    const static int moveRate = 4;
    unsigned int maxPop = tile.maxPopPerLevel * (tile.tileVariant + 1);
    // if thre is room in the zone move up 4 people form the pool into the zone
    if (pool > 0) {
        int moving = maxPop - tile.population;
        if (moving > moveRate)
            moving = moveRate;
        if (pool - moving < 0)
            moving = pool;
        pool -= moving;
        tile.population += moving;
    }
    // adjust the tile population for births and deaths
    tile.population += tile.population * rate;
    // move population that cannot be sustained by the tile into the pool
    if (tile.population > maxPop) {
        pool += tile.population - maxPop;
        tile.population = maxPop;
    }
    return tile.population;
}

void City::bulldoze(const Tile &tile)
{
    // Replace the selected tiles on the map with the tile and update
    // populations etc accordingly */
    for (int pos = 0; pos < (int) (this->map.width * this->map.height); pos++) {
        if (this->map.selected[pos] == 1){
            if(this->map.tiles[pos].tileType == TileType::RESIDENTIAL)
                this->populationPool += this->map.tiles[pos].population;
            else if(this->map.tiles[pos].tileType == TileType::COMMERCIAL)
                this->employmentPool += this->map.tiles[pos].population;
            else if(this->map.tiles[pos].tileType == TileType::INDUSTRIAL)
                this->employmentPool += this->map.tiles[pos].population;
            
            this->map.tiles[pos] = tile;
        }
    }
}

void City::shuffleTiles()
{
    while (this->shuffledTiles.size() < this->map.tiles.size())
        this->shuffledTiles.push_back(0);
    iota(shuffledTiles.begin(), shuffledTiles.end(), 1);
    random_shuffle(shuffledTiles.begin(), shuffledTiles.end());
}

void City::tileChanged()
{
    this->map.updateDirection(TileType::ROAD);
    this->map.findConnectedRegions({TileType::ROAD, TileType::RESIDENTIAL,
                TileType::COMMERCIAL, TileType::INDUSTRIAL}, 0);
}

void City::load(string cityName, std::map<string, Tile> &tileAtlas)
{
    int width = 0, height = 0;

    ifstream inputFile(cityName + "_cfg.dat", ios::in);

    string line;

    while (getline(inputFile, line)) {
        istringstream lineStream(line);
        string key;
        if (getline(lineStream, key, '=')) {
            string value;
            if (std::getline(lineStream, value)) {
                if(key == "width")                  width                   = stoi(value);
                else if(key == "height")            height                  = stoi(value);
                else if(key == "day")               this->day               = stoi(value);
                else if(key == "populationPool")    this->populationPool    = stod(value);
                else if(key == "employmentPool")    this->employmentPool    = stod(value);
                else if(key == "population")        this->population        = stod(value);
                else if(key == "employable")        this->employable        = stod(value);
                else if(key == "birthRate")         this->birthRate         = stod(value);
                else if(key == "deathRate")         this->deathRate         = stod(value);
                else if(key == "residentialTax")    this->residentialTax    = stod(value);
                else if(key == "commercialTax")     this->commercialTax     = stod(value);
                else if(key == "industrialTax")     this->industrialTax     = stod(value);
                else if(key == "funds")             this->funds             = stod(value);
                else if(key == "earnings")          this->earnings          = stod(value);
            } else 
                cerr << "Error, no value for key " << key << endl;
        }
    }
    inputFile.close();
    this->map.load(cityName + "_map.dat", width, height, tileAtlas);
    this->tileChanged();
}

void City::save(string cityName)
{
    ofstream outputFile(cityName + "_cfg.dat", ios::out);

    outputFile << "width="              << this->map.width          << endl;
    outputFile << "height="             << this->map.height         << endl;
    outputFile << "day="                << this->day                << endl;
    outputFile << "populationPool="     << this->populationPool     << endl;
    outputFile << "employmentPool="     << this->employmentPool     << endl;
    outputFile << "population="         << this->population         << endl;
    outputFile << "employable="         << this->employable         << endl;
    outputFile << "birthRate="          << this->birthRate          << endl;
    outputFile << "deathRate="          << this->deathRate          << endl;
    outputFile << "residentialTax="     << this->residentialTax     << endl;
    outputFile << "commercialTax="      << this->commercialTax      << endl;
    outputFile << "industrialTax="      << this->industrialTax      << endl;
    outputFile << "funds="              << this->funds              << endl;
    outputFile << "earnings="           << this->earnings           << endl;
    outputFile.close();
    this->map.save(cityName + "_map.dat");
}

void City::update(float dt)
{
    double popTotal = 0, commercialRevenue = 0, industrialRevenue = 0;
    // update game time
    this->currentTime += dt;
    if (this->currentTime < this->timePerDay)
        return;
    ++this->day;
    this->currentTime = 0.0;
    if (this->day % 30 == 0) {
        this->funds += this->earnings;
        this->earnings = 0;
    }
    // handle pool distribution
    for (int i = 0; i < (int) this->map.tiles.size(); i++) {
        Tile &tile = this->map.tiles[this->shuffledTiles[i]];
        if (tile.tileType == TileType::RESIDENTIAL) {
            // Redistribute the pool and increase the population total by the
            // tile's population 
            this->distributePool(this->populationPool, tile,
                                 this->birthRate - this->deathRate);
            popTotal += tile.population;
        } else if (tile.tileType == TileType::COMMERCIAL) {
            // hire people
            if (rand() % 100 < 15 * (1.0 - this->commercialTax))
                this->distributePool(this->employmentPool, tile, 0.00);
        } else if (tile.tileType == TileType::INDUSTRIAL) {
            // extract resources from the ground
            if (this->map.resources[i] > 0 && rand() % 100 < this->population) {
                ++tile.production;
                --this->map.resources[i];
            }
            // hire people
            if (rand() % 100 < 15 * (1.0 - this->industrialTax))
                this->distributePool(this->employmentPool, tile, 0.0);
        }
        tile.update();
    }
    // Handles goods manufacture
    for (int i = 0; i < (int) this->map.tiles.size(); i++) {
        Tile &tile = this->map.tiles[this->shuffledTiles[i]];
        if (tile.tileType == TileType::INDUSTRIAL) {
            int receivedResources = 0;
            // Receive resources from smaller and connected zones
            for (auto& tile2 : this->map.tiles) {
                if (tile2.regions[0] == tile.regions[0] &&
                    tile2.tileType == TileType::INDUSTRIAL)
                {
                    if (tile2.production > 0) {
                        ++receivedResources;
                        --tile2.production;
                    }
                    if (receivedResources >= tile.tileVariant + 1)
                        break;
                }
            }
            // Turn resources into goods
            tile.storedGoods += (receivedResources+tile.production) *
                (tile.tileVariant + 1);
        }
    }
    // Handle good distribution
    for (int i = 0; i < (int) this->map.tiles.size(); i++) {
        Tile &tile = this->map.tiles[this->shuffledTiles[i]];
        if (tile.tileType == TileType::COMMERCIAL) {
            int receivedGoods = 0;
            double maxCustomers = 0.0;
            for (auto &tile2 : this->map.tiles) {
                if (tile2.regions[0] == tile.regions[0] &&
                    tile2.tileType == TileType::INDUSTRIAL &&
                    tile2.storedGoods > 0)
                {
                    while (tile2.storedGoods > 0 &&
                           receivedGoods != tile.tileVariant + 1)
                    {
                        --tile2.storedGoods;
                        ++receivedGoods;
                        industrialRevenue += 100 * (1.0-industrialTax);
                    }
                }
                else if (tile2.regions[0] == tile.regions[0] &&
                        tile2.tileType == TileType::RESIDENTIAL)
                {
                    maxCustomers += tile2.population;
                }
                if (receivedGoods == tile.tileVariant + 1)
                    break;
            }
            /* Calculate the overall revenue for the tile. */
            tile.production = (receivedGoods * 100.0 + rand() % 20) *
                (1.0 - this->commercialTax);

            double revenue = tile.production * maxCustomers
                * tile.population / 100.0;
            commercialRevenue += revenue;
        }
    }
    // Adjut population pool for births and deaths
    this->populationPool += this->populationPool *
        (this->birthRate - this->deathRate);
    popTotal += this->populationPool;
    // Ajust employment pool for the changing population
    float newWorkers = (popTotal - this->population) * this->propCanWork;
    newWorkers *= newWorkers < 0 ? -1 : 1;
    this->employmentPool += newWorkers;
    this->employable += newWorkers;
    if (this->employmentPool < 0)
        this->employmentPool = 0;
    if (this->employable < 0)
        this->employable = 0;

    // Update the city population
    this->population = popTotal;

    // Calculate city income from tax.
    this->earnings = (this->population - this->populationPool) * 15
        * this->residentialTax;
    this->earnings += commercialRevenue * this->commercialTax;
    this->earnings += industrialRevenue * this->industrialTax;
}
