#include <string>
#include "Character.hpp"
#include "Stats.hpp"
#include "Mage.hpp"
#include "Game.hpp"
#include "GameStateInit.hpp"

int main()
{
    Mage m;
    Stats base(16, 1, 3, 2, 9, 2, 4, 5, 1, 0);
    std::string erika("Erika");
    Character c(erika, base, &m);
    
    Game game;
    game.pushState(new GameStateInit(&game));
    game.gameLoop();
    return 0;
}
