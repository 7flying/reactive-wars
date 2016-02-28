#include <string>
#include "Character.hpp"
#include "Stats.hpp"
#include "Mage.hpp"

int main()
{
    Mage m;
    Stats base(16, 1, 3, 2, 9, 2, 4, 5, 1, 0);
    std::string erika("Erika");
    Character c(erika, base, &m);
}
