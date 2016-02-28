#include "Character.hpp"


Character::Character(string &name, Stats &accumStats,
                     CharacterClass *characterClass)
{
    this->name = name;
    this->accumStats = accumStats;
    this->characterClass = *characterClass;
}
