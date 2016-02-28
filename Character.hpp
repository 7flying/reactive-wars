#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "Stats.hpp"
#include "CharacterClass.hpp"

using namespace sf;
using namespace std;

class Character {

public:
    string name;
    Stats accumStats;
    CharacterClass characterClass;

    Character(string &name, Stats &accumStats, CharacterClass *characterClass);
    
};

#endif
