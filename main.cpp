#pragma once
#include <SFML/Graphics.hpp>
#include "bootstrap.h"
#include "loop.h"
#include "map_Base.h"
#include "ui_Inventory.h"

int main()
{
    Audio::bootstrap();
    Font::bootstrap();


    sf::Clock clock;

    // CREATING PLAYER VARIABLES
    sf::RectangleShape shape({ 10.f, 20.f });
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(WIDTH / 2, HEIGHT / 2);

    // PLAYER CREATION
    int playerid = PlayerHelper::createPlayer({ WIDTH / 2, HEIGHT / 2 }, shape);
    std::cout << playerid << std::endl;

    // CAMERA VIEW
    view.reset(sf::FloatRect(0, 0, WIDTH, HEIGHT));
    view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    window.setView(view);

    uiView.reset(sf::FloatRect(-2000, -2000, WIDTH, HEIGHT));
    uiView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

    AIHelper::createAI(FIREWALLGRUNT, { WIDTH / 4, HEIGHT / 2 });

    Map::load(Map::LEVEL0);

    LadderObjectHelper::createLadder(14, { 1750, 485 }, { 4,4 }, { 1835, 400 });
    
    //creating ui
    UIHealthHelper::createHealthBar(*PlayerHelper::list.at(playerid));
    UIToolboxHelper::createToolbox();
    UIInventoryHelper::createInventory();

    sf::Clock fpsclock;
    fpsclock.restart();
    sf::Text fpsctr;
    fpsctr.setFont(Font::arial);
    fpsctr.setCharacterSize(13);
    fpsctr.setString("");

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

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
                Map::mapSprite.move({ -50, 0 });
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
                Map::mapSprite.move({ 50, 0 });
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
                Map::mapSprite.move({ 0, -50 });
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
                Map::mapSprite.move({ 0, 50 });
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::K) {
                PlayerHelper::list.at(playerid)->hurt(10.0f);// health -= 10.0f;

                //view.rotate(-10.f);
            }


            if (event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left) {
                UIToolboxHelper::list[0]->mutex = false;
            }
            if (event.type == sf::Event::Resized) {
                WIDTH = window.getSize().x;
                HEIGHT = window.getSize().y;
                window.setSize({(unsigned int)WIDTH, (unsigned int)HEIGHT});
                window.setPosition({ 0, 0 });
            }

        }

        if (PlayerHelper::list.at(playerid)->health <= 0.0f) {
            EndCondition = true;
        }

        float currentTime = clock.restart().asSeconds();
        physics::dt = currentTime * 10;
        int fps = 1.0f / currentTime;

        fpsctr.setString("X" + std::to_string(PlayerHelper::list.at(playerid)->position.x) + " Y" + std::to_string(PlayerHelper::list.at(playerid)->position.y));

        simulate();

        // DRAWING
        window.draw(Map::mapSprite);

        for (auto pair : BaseObjectHelper::list) {
            auto object = pair.second;
            for (auto drawable : object->drawableList) {
                window.draw(*drawable.second);
            }

        }

        for (auto player : PlayerHelper::list) {
            window.draw(*player.second->drawable);
            window.draw(player.second->sprite);
        }

        for (auto AI : AIHelper::list) {
            window.draw(*AI.second->drawable);
            window.draw(AI.second->sprite);
            window.draw(AI.second->healthText);
        }

        for (auto pair : PlatformHelper::list) {
            window.draw(*pair.second->drawable);
        }

        for (auto bullet : BulletHelper::list) {
            if (!bullet.second->checkForHit()) {
                bullet.second->simStep(physics::dt);
                window.draw(*bullet.second->drawable);
            }
            else {
                BulletHelper::list.erase(bullet.second->id);
            }

            if (bullet.second->clock.getElapsedTime() > sf::seconds(10)) {
                BulletHelper::list.erase(bullet.second->id);
            }
        }

        
        

        // DRAW UI VIEW SECTION
        window.setView(uiView);
        for (auto invIcon : UIInventorySlotHelper::list) {
            auto pixelpos = invIcon.second->getPosition();

            sf::Vector2f xy = { view.getViewport().left, view.getViewport().top };
            invIcon.second->setPosition(pixelpos - xy);
            invIcon.second->draw();
        }


        for (auto healthbar : UIHealthHelper::list) {
            healthbar.second->update();
            for (auto drawable : healthbar.second->drawableList) {
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

        fpsctr.setPosition(10 - 2000, HEIGHT - 30 - 2000);
        window.draw(fpsctr);


        /////////////////////


        window.setView(view);
        //UIToolboxHelper::list[0]->update((sf::Vector2f)sf::Mouse::getPosition(window));

        //if (fpsclock.getElapsedTime().asSeconds() > 1.0f) {
          //  std::cout << fpsclock.getElapsedTime().asSeconds() << std::endl;

        fpsclock.restart();

        window.display();
    }

    return 0;
}