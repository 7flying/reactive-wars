#ifndef CHARACTER_CLASS_HPP
#define CHARACTER_CLASS_HPP

#include <string>
#include "Stats.hpp"

using namespace std;

class CharacterClass {
public:
    string name;
    Stats baseStats;

    CharacterClass(){};
    CharacterClass(string &name, Stats &baseStats);
};

#endif // CHARACTER_CLASS_HPP
