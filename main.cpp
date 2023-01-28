#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Player.h"
#include "Platform.h"

#include "PhysicsSystem.h"
#include "Includes.h"

#include "ui_Element.h"
#include "ui_Health.h"
#include "ui_Button.h"
#include "ui_Toolbox.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");

    sf::Clock clock;

    // CREATING PLAYER VARIABLES
    sf::RectangleShape shape({ 10.f, 20.f });
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(WIDTH / 2, HEIGHT / 2);

    // PLAYER CREATION
    std::cout << PlayerHelper::createPlayer({ WIDTH / 2, HEIGHT / 2 }, shape) << std::endl;

    sf::RectangleShape surfaceCheck;

    // floor0
    sf::RectangleShape floor0({ WIDTH * 3, 10 });
    floor0.setFillColor(sf::Color::Red);
    floor0.setPosition(-WIDTH, HEIGHT - 10);

    std::cout << PlatformHelper::createPlatform({ -WIDTH, HEIGHT - 10 }, floor0) << std::endl;

    // floor1
    sf::RectangleShape floor1({ 100, 10 });
    floor1.setFillColor(sf::Color::Red);
    floor1.setPosition(0, HEIGHT - 100);

    std::cout << PlatformHelper::createPlatform({ 0, HEIGHT - 100 }, floor1) << std::endl;

    // floor2
    sf::RectangleShape floor2({ 100, 10 });
    floor2.setFillColor(sf::Color::Red);
    floor2.setPosition(400, HEIGHT - 30);

    std::cout << PlatformHelper::createPlatform({ 300, HEIGHT - 30 }, floor2) << std::endl;

    // floor3
    sf::RectangleShape floor3({ 100, 100 });
    floor3.setFillColor(sf::Color::Red);
    floor3.setPosition(500, HEIGHT - 130);

    std::cout << PlatformHelper::createPlatform({ 500, HEIGHT - 130 }, floor3) << std::endl;


    //creating ui
    UIHealthHelper::createHealthBar();
    UIToolboxHelper::createToolbox();


    //UIButtonHelper::createButton({ 75,400 }, TINY, sf::Color(0xffffffaa), std::string("Click Me"));
    //UIButtonHelper::createButton({ 150,400 }, SMALL, sf::Color(0xffffffaa), std::string("Click Me"));
    //UIButtonHelper::createButton({ 250,400 }, MEDIUM, sf::Color(0xffffffaa), std::string("Click Me"));
    //UIButtonHelper::createButton({ 400,400 }, LARGE, sf::Color(0xffffffaa), std::string("Click Me"));
    //UIButtonHelper::createButton({ 600,400 }, MASSIVE, sf::Color(0xffffffaa), std::string("Click Me"));

    std::string collLocation;
    while (window.isOpen())
    {
        window.clear(sf::Color(51, 77, 104, 255));

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::S) {
                for (auto player : PlayerHelper::list) {
                    player.second->unduck();
                }
            }
            if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left) {
                UIToolboxHelper::list[0]->mutex = false;
            }
            if (event.type == sf::Event::Resized) {
                WIDTH = window.getSize().x;
                HEIGHT = window.getSize().y;
            }
        }

        
        //determine which side the collision is on
        

        float currentTime = clock.restart().asSeconds();
        physics::dt = currentTime * 10;
        int fps = 1.0f / currentTime;
        //player.simStep(physics::dt);


        int collisionCount = 0;
        for (auto ent1 : PlayerHelper::list) {
            for (auto ent2 : PlatformHelper::list) {
                int collisionNumber = physics::handleCollision(*ent2.second->drawable, *ent1.second->drawable);

                surfaceCheck.setPosition(ent1.second->position.x, ent1.second->position.y + ent1.second->drawable->getSize().y);
                surfaceCheck.setSize({ ent1.second->drawable->getSize().x, 2 });

                if (physics::isCollided(surfaceCheck, *ent2.second->drawable)) {
                    collisionCount++;
                    //std::cout << "player is on surface" << std::endl;
                    ent1.second->onSurface = true;
                }
                
                if (collisionNumber != 0) {
                    //std::cout << "collision " << collisionNumber << std::endl;
                    collisionCount++;
                    
                    if (collisionNumber == 3) {
                            ent1.second->airborne = false;
                            ent1.second->velocity = { ent1.second->velocity.x, 0 };
                            ent1.second->acceleration = { 0, 0 };
                    }
                    else if (collisionNumber == 1 || collisionNumber == 2) {
                            ent1.second->airborne = true;
                            ent1.second->velocity = { ent1.second->velocity.x, ent1.second->velocity.y };
                            ent1.second->acceleration = { 0, 9.81f };
                    }
                    else if (collisionNumber == 4) {
                        ent1.second->airborne = true;
                        ent1.second->velocity = { ent1.second->velocity.x, -ent1.second->velocity.y * 0.5f };
                        ent1.second->acceleration = { 0, 9.81f };
                    }

                    physics::resolveCollision(*ent2.second, *ent1.second, collisionNumber);

                    //apply upwards force to player equal to negative acceleration
                }    
            }
            if (collisionCount == 0) {
                ent1.second->acceleration = { 0, 9.81f };
            }
        } 

        for (auto player : PlayerHelper::list) {
            player.second->simStep(physics::dt);

            auto pos = player.second->position;
            auto dif = pos - sf::Vector2f(WIDTH / 2, HEIGHT / 2);

            player.second->move();

            if (pos.x < WIDTH / 4) {
                player.second->position.x = (WIDTH / 4) + 1;
                player.second->updateShape();
                for (auto ent : EntityHelper::list) {
                    if (ent.first != player.first) {
                        ent.second->position.x += 1.5f;
                        ent.second->drawable->setPosition({ ent.second->drawable->getPosition().x + 1.5f ,ent.second->drawable->getPosition().y });
                    }
                }
            }
            
            if (pos.x + player.second->drawable->getSize().x > WIDTH - (WIDTH / 4)) {
                player.second->position.x = WIDTH - (WIDTH / 4) - player.second->drawable->getSize().x - 1;
                player.second->updateShape();
                for (auto ent : EntityHelper::list) {
                    if (ent.first != player.first) {
                        ent.second->position.x -= 1.5f;
                        ent.second->drawable->setPosition({ ent.second->drawable->getPosition().x - 1.5f ,ent.second->drawable->getPosition().y });
                    }
                }
            }

            window.draw(*player.second->drawable);
        }

        for (auto pair : PlatformHelper::list) {
            window.draw(*pair.second->drawable);
        }
        
        for (auto uielement : UIElementHelper::list) {
            for (auto drawable : uielement.second->drawableList) {
                window.draw(*drawable.second);
            }
        }

        for (auto button : UIButtonHelper::list) {
            button.second->update((sf::Vector2f)sf::Mouse::getPosition(window));
            button.second->render(window);
            if (button.second->isClicked()) {
                //std::cout << "click" << std::endl;
            }
        }

        UIToolboxHelper::list[0]->update((sf::Vector2f)sf::Mouse::getPosition(window));

        window.display();
    }

    return 0;
}