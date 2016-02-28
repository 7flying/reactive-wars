#ifndef STATS_HPP
#define STATS_HPP


class Stats {

public:
    unsigned int hp, strma, skill, speed, luck, def, res, mov, level, exp;

    Stats();
    Stats(unsigned int hp, unsigned int strma, unsigned int skill,
          unsigned int speed, unsigned int luck, unsigned int def,
          unsigned int res, unsigned int mov, unsigned int level,
          unsigned int exp);
};

#endif
