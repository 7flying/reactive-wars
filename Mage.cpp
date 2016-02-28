#include "Mage.hpp"
#include "Stats.hpp"

Mage::Mage()
{
    this->name = "Mage";
    Stats base(16, 1, 3, 2, 9, 2, 4, 5, 1, 0);
    this->baseStats = base;
}
