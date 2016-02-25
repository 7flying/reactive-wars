#include <stack>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Game.hpp"
#include "GameState.hpp"


Game::Game()
{
    this->loadTextures();
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
}
