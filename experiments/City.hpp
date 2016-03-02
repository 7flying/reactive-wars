#ifndef CITY_HPP
#define CITY_HPP

#include <vector>
#include <map>
#include <string>
#include "Map.hpp"

using namespace std;


class City
{
private:
    float currentTime, timePerDay;
    vector<int> shuffledTiles;
    /** Number of residents who are not in a residential zone. **/
    double populationPool;
    /** Number of residents who are not currently employed but can work. **/
    double employmentPool;
    /** Proportion of citizens who can work **/
    float propCanWork;
    /* Proportion of residents who die/give birth each day.
     * Estimate for death rate = 1 / (life expectancy * 360)
     * Current world values are 0.000055 and 0.000023, respectively */
    double birthRate, deathRate;

    double distributePool(double &pool, Tile &tile, double rate);

public:

    Map map;
    double population, employable, residentialTax, commercialTax, industrialTax;
    /** Running total of city earnings this month **/
    double earnings, funds;
    int day;

    City();
    City(string cityName, int tileSize, std::map<string, Tile> &tileAtlas);

    void load(string cityName, std::map<string, Tile> &tileAtlas);
    void save(string cityName);

    void update(float dt);
    void bulldoze(const Tile &tile);
    void shuffleTiles();
    void tileChanged();

    double getHomeless() { return this->populationPool; }
    double getUnemployd() { return this->employmentPool; }
    
};

#endif // CITY_HPP
