#include <SFML/Graphics.hpp>
#include "GameStateStart.hpp"
#include "GameStateEditor.hpp"
#include "GameState.hpp"
#include "Gui.hpp"


GameStateStart::GameStateStart(Game *game)
{
    this->game = game;
    Vector2f pos = Vector2f(this->game->window.getSize());
    this->view.setSize(pos);
    pos *= 0.5f;
    this->view.setCenter(pos);

    // we must use emplace because [] works by first creating an empty object
    // of the type (calling the empty constructor), then copies the object to
    // the right of the = into the map. But Gui does not have an empty construc.
    this->guiSystem.emplace("menu", Gui(Vector2f(192, 32), 4, false,
                                        this->game->stylesheets.at("button"),
                                        // defined at header <utility>
                                        {make_pair("Load Game", "load_game")}));
    this->guiSystem.at("menu").setPosition(pos);
    this->guiSystem.at("menu").setOrigin(96, 32 * 0.5);
    this->guiSystem.at("menu").show();
}

void GameStateStart::draw(const float dt)
{
    this->game->window.setView(this->view);
    this->game->window.clear(Color::Black);
    this->game->window.draw(this->game->background);

    for (auto gui: this->guiSystem) {
        // we are iterating over a map, we access the key with 'first' and
        // the value with 'second'
        this->game->window.draw(gui.second);
    }
}

void GameStateStart::update(const float dt)
{
    
}

void GameStateStart::handleInput()
{
    Event event;
    Vector2f mousePos = this->game->window.mapPixelToCoords(
        Mouse::getPosition(this->game->window), this->view);
    while (this->game->window.pollEvent(event)) {
        switch(event.type) {
        case Event::Closed:{
            game->window.close();
            break;
        }
        case Event::Resized:{
            this->view.setSize(event.size.width, event.size.height);
            this->game->background.setPosition(
                // Convert a position in window coordinates to its equivalent
                // position in world coordinates usint the current view
                this->game->window.mapPixelToCoords(Vector2i(0, 0)));
            this->game->background.setScale(
                float(event.size.width) / float(
                    this->game->background.getTexture()->getSize().x),
                float(event.size.width) / float(
                    this->game->background.getTexture()->getSize().y));
            // menu
            Vector2f pos = Vector2f(event.size.width, event.size.height);
            pos *= 0.5f;
            pos = this->game->window.mapPixelToCoords(Vector2i(pos), this->view);
            this->guiSystem.at("menu").setPosition(pos);
            break;
        }
        case Event::MouseMoved:{
            this->guiSystem.at("menu").highlight(
                this->guiSystem.at("menu").getEntry(mousePos));
            break;
        }
        case Event::MouseButtonPressed:{
            if (event.mouseButton.button == Mouse::Left) {
                string msg = this->guiSystem.at("menu").activate(mousePos);
                if (msg == "load_game")
                    this->loadgame();
            }
        }
        case Event::KeyPressed:{
            if (event.key.code == Keyboard::Escape)
                this->game->window.close();
            else if (event.key.code == Keyboard::Space)
                this->loadgame();
            break;
        }
        default:
            break;
        }
    }
}

void GameStateStart::loadgame()
{
    this->game->pushState(new GameStateEditor(this->game));
}
