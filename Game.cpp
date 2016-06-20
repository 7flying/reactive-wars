#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Game.hpp"
#include "GameState.hpp"
#include "Else.hpp"


Game::Game()
{
    // Load everything
    this->loadFonts();
    this->loadTextures();
    this->loadTiles();
    // Create main window
    this->window.create(VideoMode(Game::WIN_WIDTH, Game::WIN_HEIGHT),
                        "Reactive Wars");
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
    while (this->window.isOpen()) {
        Time elapsed = clock.restart();
        if (this->peekState() == nullptr)
            continue;
        this->peekState()->handleInput();
        this->peekState()->update(elapsed);
        this->window.clear(Color::Black);
        this->peekState()->draw(elapsed);
        this->window.display();
    }
}

void Game::loadFonts()
{
    this->fontman.loadFont("ds-bios", "media" + getFileSeparator()
                           + "Nintendo-DS-BIOS.ttf");
}

void Game::loadTextures()
{
    //this->texman.loadTexture("background-rainbow", "media" + getFileSeparator()
    //                         + "rainbow-glitch.png");
    this->texman.loadTexture("background", "media/background.png");
    this->texman.loadTexture("grass", "media/grass.png");
    this->texman.loadTexture("grass1", "media/grass1.png");
    this->texman.loadTexture("grass2", "media/grass2.png");
    this->texman.loadTexture("grass3", "media/grass3.png");
    this->texman.loadTexture("moun", "media/moun.png");
    this->texman.loadTexture("moun1", "media/moun1.png");
    this->texman.loadTexture("water", "media/water.png");
    this->texman.loadTexture("water1", "media/water1.png");
    this->texman.loadTexture("water2", "media/water2.png");

    this->texman.loadTexture("red-soldier", "media/red-soldier.png");
    this->texman.loadTexture("black-soldier", "media/black-soldier.png");
}

void Game::loadTiles()
{
    Animation staticAnim(0, 0, 1.0f);
    this->tileAtlas["grass"] = Tile(this->tileSize, 1, texman.getRef("grass"),
                                    { staticAnim },
                                    TileType::GRASS);
    this->tileAtlas["grass1"] = Tile(this->tileSize, 1, texman.getRef("grass1"),
                                     { staticAnim },
                                     TileType::GRASS1);
    this->tileAtlas["grass2"] = Tile(this->tileSize, 1, texman.getRef("grass2"),
                                     { staticAnim },
                                     TileType::GRASS2);
    this->tileAtlas["grass3"] = Tile(this->tileSize, 1, texman.getRef("grass3"),
                                     { staticAnim },
                                     TileType::GRASS3);
    this->tileAtlas["moun"] = Tile(this->tileSize, 1, texman.getRef("moun"),
                                   { staticAnim },
                                   TileType::MOUNTAIN);
    this->tileAtlas["moun1"] = Tile(this->tileSize, 1, texman.getRef("moun1"),
                                    { staticAnim },
                                    TileType::MOUNTAIN1);
    this->tileAtlas["water"] = Tile(this->tileSize, 1, texman.getRef("water"),
                                    { Animation(0, 3, 0.5f),
                                            Animation(0, 3, 0.5f),
                                            Animation(0, 3, 0.5f) },
                                    TileType::WATER);
    this->tileAtlas["water1"] = Tile(this->tileSize, 1, texman.getRef("water1"),
                                     { Animation(0, 3, 0.5f),
                                             Animation(0, 3, 0.5f),
                                             Animation(0, 3, 0.5f) },
                                     TileType::WATER1);
    this->tileAtlas["water2"] = Tile(this->tileSize, 1, texman.getRef("water2"),
                                     { Animation(0, 3, 0.5f),
                                             Animation(0, 3, 0.5f),
                                             Animation(0, 3, 0.5f) },
                                     TileType::WATER2);
    this->tileAtlas["red-soldier"] = Tile(this->unitTileSize, 1,
                                          texman.getRef("red-soldier"),
                                          { Animation(0, 3, 0.5f),
                                                  Animation(0, 3, 0.5f),
                                                  Animation(0, 3, 0.5f)},
                                          TileType::REDSOLDIER);
    this->tileAtlas["black-soldier"] = Tile(this->unitTileSize, 1,
                                          texman.getRef("black-soldier"),
                                          { Animation(0, 3, 0.5f),
                                                  Animation(0, 3, 0.5f),
                                                  Animation(0, 3, 0.5f)},
                                            TileType::BLACKSOLDIER);
}
