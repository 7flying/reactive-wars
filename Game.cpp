#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Game.hpp"
#include "Else.hpp"


Game::Game()
{
    this->window.create(VideoMode(800, 600), "Reactive Wars");
    this->window.setFramerateLimit(60);
    this->loadFonts();
    this->loadTextures();
    this->background.setTexture(this->texman.getRef("background-rainbow"));
}

Game::~Game()
{
    
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
        float deltaTime = elapsed.asSeconds();

        if (this->peekState() == nullptr)
            continue;
        this->peekState()->handleInput();
        this->peekState()->update(deltaTime);
        this->window.clear(Color::Black);
        this->peekState()->draw(deltaTime);
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
    this->texman.loadTexture("background-rainbow", "media" + getFileSeparator()
                             + "rainbow-glitch.png");
}
