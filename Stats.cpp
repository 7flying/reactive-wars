#include "Stats.hpp"

Stats::Stats()
{
    this->hp = 0;
    this->strma = 0;
    this->skill = 0;
    this->speed = 0;
    this->luck = 0;
    this->def = 0;
    this->res = 0;
    this->mov = 0;
    this->level = 0;
}

Stats::Stats(unsigned int hp, unsigned int strma, unsigned int skill,
             unsigned int speed, unsigned int luck, unsigned int def,
             unsigned int res, unsigned int mov, unsigned int level,
             unsigned int exp)
{
    this->hp = hp;
    this->strma = strma;
    this->skill = skill;
    this->speed = speed;
    this->luck = luck;
    this->def = def;
    this->res = res;
    this->mov = mov;
    this->level = level;
    this->exp = exp;
}
