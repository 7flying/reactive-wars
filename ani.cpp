#include <SFML/Graphics.hpp>
#include "AnimatedSprite.hpp"
#include <iostream>

int main()
{
    // setup window
    sf::Vector2i screenDimensions(800,600);
    sf::RenderWindow window(sf::VideoMode(screenDimensions.x, screenDimensions.y), "Animations!");
    window.setFramerateLimit(60);

    // load texture (spritesheet)
    sf::Texture texture;
    if (!texture.loadFromFile("skeletton.png"))
    {
        std::cout << "Failed to load player spritesheet!" << std::endl;
        return 1;
    }

    // set up the animations for all four directions (set spritesheet and push frames)
    /*Animation walkingAnimationDown;
    walkingAnimationDown.setSpriteSheet(texture);
    walkingAnimationDown.addFrame(sf::IntRect(224, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(192, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(160, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(128, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(96, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect( 0, 0, 32, 32));

    Animation walkingAnimationLeft;
    walkingAnimationLeft.setSpriteSheet(texture);
    walkingAnimationLeft.addFrame(sf::IntRect(224, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(192, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(160, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(128, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(96, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect( 0, 32, 32, 32));

    Animation walkingAnimationRight;
    walkingAnimationRight.setSpriteSheet(texture);
    walkingAnimationRight.addFrame(sf::IntRect(224, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(192, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(160, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(128, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(96, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(64, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect( 0, 64, 32, 32));

    Animation walkingAnimationUp;
    walkingAnimationUp.setSpriteSheet(texture);
    walkingAnimationUp.addFrame(sf::IntRect(224, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(192, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(160, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(128, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(96, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect( 0, 96, 32, 32));
    */
    Animation walkingAnimationDown;
    walkingAnimationDown.setSpriteSheet(texture);
    walkingAnimationDown.addFrame(sf::IntRect(126, 0, 18, 20));
    walkingAnimationDown.addFrame(sf::IntRect(108, 0, 18, 20));
    walkingAnimationDown.addFrame(sf::IntRect(90, 0, 18, 20));
    walkingAnimationDown.addFrame(sf::IntRect(72, 0, 18, 20));
    walkingAnimationDown.addFrame(sf::IntRect(54, 0, 18, 20));
    walkingAnimationDown.addFrame(sf::IntRect(36, 0, 18, 20));
    walkingAnimationDown.addFrame(sf::IntRect(18, 0, 18, 20));
    walkingAnimationDown.addFrame(sf::IntRect( 0, 0, 18, 20));

    Animation walkingAnimationLeft;
    walkingAnimationLeft.setSpriteSheet(texture);
    walkingAnimationLeft.addFrame(sf::IntRect(126, 20, 18, 20));
    walkingAnimationLeft.addFrame(sf::IntRect(108, 20, 18, 20));
    walkingAnimationLeft.addFrame(sf::IntRect(90, 20, 18, 20));
    walkingAnimationLeft.addFrame(sf::IntRect(72, 20, 18, 20));
    walkingAnimationLeft.addFrame(sf::IntRect(54, 20, 18, 20));
    walkingAnimationLeft.addFrame(sf::IntRect(36, 20, 18, 20));
    walkingAnimationLeft.addFrame(sf::IntRect(18, 20, 18, 20));
    walkingAnimationLeft.addFrame(sf::IntRect( 0, 20,  18, 20));

    Animation walkingAnimationRight;
    walkingAnimationRight.setSpriteSheet(texture);
    walkingAnimationRight.addFrame(sf::IntRect(126, 40, 18, 20));
    walkingAnimationRight.addFrame(sf::IntRect(108, 40, 18, 20));
    walkingAnimationRight.addFrame(sf::IntRect(90, 40, 18, 20));
    walkingAnimationRight.addFrame(sf::IntRect(72, 40, 18, 20));
    walkingAnimationRight.addFrame(sf::IntRect(54, 40, 18, 20));
    walkingAnimationRight.addFrame(sf::IntRect(36, 40, 18, 20));
    walkingAnimationRight.addFrame(sf::IntRect(18, 40, 18, 20));
    walkingAnimationRight.addFrame(sf::IntRect( 0, 40, 18, 20));

    Animation walkingAnimationUp;
    walkingAnimationUp.setSpriteSheet(texture);
    walkingAnimationUp.addFrame(sf::IntRect(126, 60, 18, 20));
    walkingAnimationUp.addFrame(sf::IntRect(108, 60, 18, 20));
    walkingAnimationUp.addFrame(sf::IntRect(90, 60, 18, 20));
    walkingAnimationUp.addFrame(sf::IntRect(72, 60,  18, 20));
    walkingAnimationUp.addFrame(sf::IntRect(54, 60,  18, 20));
    walkingAnimationUp.addFrame(sf::IntRect(36, 60,  18, 20));
    walkingAnimationUp.addFrame(sf::IntRect(18, 60,  18, 20));
    walkingAnimationUp.addFrame(sf::IntRect( 0, 60,  18, 20));
    

    Animation* currentAnimation = &walkingAnimationDown;

    // set up AnimatedSprite
    AnimatedSprite animatedSprite(sf::seconds(0.2), true, false);
    animatedSprite.setPosition(sf::Vector2f(screenDimensions / 2));

    sf::Clock frameClock;

    float speed = 80.f;
    bool noKeyWasPressed = true;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                window.close();
        }

        sf::Time frameTime = frameClock.restart();

        // if a key was pressed set the correct animation and move correctly
        sf::Vector2f movement(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            currentAnimation = &walkingAnimationUp;
            movement.y -= speed;
            noKeyWasPressed = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            currentAnimation = &walkingAnimationDown;
            movement.y += speed;
            noKeyWasPressed = false;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            currentAnimation = &walkingAnimationLeft;
            movement.x -= speed;
            noKeyWasPressed = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            currentAnimation = &walkingAnimationRight;
            movement.x += speed;
            noKeyWasPressed = false;
        }
        animatedSprite.play(*currentAnimation);
        animatedSprite.move(movement * frameTime.asSeconds());

        // if no key was pressed stop the animation
        if (noKeyWasPressed)
        {
            animatedSprite.stop();
        }
        noKeyWasPressed = true;

        // update AnimatedSprite
        animatedSprite.update(frameTime);

        // draw
        window.clear();
        window.draw(animatedSprite);
        window.display();
    }

    return 0;
}
