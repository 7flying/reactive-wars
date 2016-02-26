#include <stack>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Game.hpp"
#include "GameState.hpp"


Game::Game()
{
    this->loadTextures();
    this->loadTiles();
    this->window.create(VideoMode(800, 600), "Reactive Wars");
    this->window.setFramerateLimit(60);
    this->background.setTexture(this->texman.getRef("background"));
}

Game::~Game()
{
    while (!this->states.empty())
        popState();
}

void Game::pushState(GameState *state)
{
    this->states.push(state);
}

void Game::popState()
{
    delete this->states.top();
    this->states.pop();
}

void Game::changeState(GameState *state)
{
    if (!this->states.empty())
        popState();
    pushState(state);
}

GameState* Game::peekState()
{
    if (this->states.empty())
        return nullptr;
    return this->states.top();
}

void Game::gameLoop()
{
    Clock clock;
 
    while (this->window.isOpen())
    {
        Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        if (peekState() == nullptr)
            continue;
        peekState()->handleInput();
        peekState()->update(dt);
        this->window.clear(Color::Black);
        peekState()->draw(dt);
        this->window.display();
    }
}

void Game::loadTextures()
{
    this->texman.loadTexture("background", "media/background.png");
    this->texman.loadTexture("grass", "media/grass.png");
    this->texman.loadTexture("forest", "media/forest.png");
    this->texman.loadTexture("water", "media/water.png");
    this->texman.loadTexture("residential", "media/residential.png");
    this->texman.loadTexture("commercial", "media/commercial.png");
    this->texman.loadTexture("industrial", "media/industrial.png");
    this->texman.loadTexture("road", "media/road.png");
}

void Game::loadTiles()
{
    Animation staticAnim(0, 0, 1.0f);
    this->tileAtlas["grass"] = Tile(this->tileSize, 1, texman.getRef("grass"),
                                    { staticAnim },
                                    TileType::GRASS, 50, 0, 1);
    tileAtlas["forest"] = Tile(this->tileSize, 1, texman.getRef("forest"),
                               { staticAnim },
                               TileType::FOREST, 100, 0, 1);
    tileAtlas["water"] = Tile(this->tileSize, 1, texman.getRef("water"),
                              { Animation(0, 3, 0.5f), Animation(0, 3, 0.5f),
                                      Animation(0, 3, 0.5f) },
                              TileType::WATER, 0, 0, 1);
    tileAtlas["residential"] = Tile(this->tileSize, 2,
                                    texman.getRef("residential"),
                                    { staticAnim, staticAnim, staticAnim,
                                            staticAnim, staticAnim,
                                            staticAnim },
                                    TileType::RESIDENTIAL, 300, 50, 6);
    tileAtlas["commercial"] = Tile(this->tileSize, 2,
                                   texman.getRef("commercial"),
                                   { staticAnim, staticAnim, staticAnim,
                                           staticAnim},
                                   TileType::COMMERCIAL, 300, 50, 4);
    tileAtlas["industrial"] = Tile(this->tileSize, 2,
                                   texman.getRef("industrial"),
                                   { staticAnim, staticAnim, staticAnim,
                                           staticAnim },
                                   TileType::INDUSTRIAL, 300, 50, 4);
    tileAtlas["road"] = Tile(this->tileSize, 1, texman.getRef("road"),
                             { staticAnim, staticAnim, staticAnim, staticAnim,
                                     staticAnim, staticAnim, staticAnim,
                                     staticAnim, staticAnim, staticAnim,
                                     staticAnim },
                             TileType::ROAD, 100, 0, 1);
}
