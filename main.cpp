#pragma once
#include <SFML/Graphics.hpp>
#include "bootstrap.h"
#include "loop.h"
#include "map_Base.h"
#include "ui_Inventory.h"
#include "Inventory.h"

int main()
{
    // CREATING PLAYER VARIABLES


    // PLAYER CREATION
    int playerid = PlayerHelper::createPlayer({ 390, 700 }); //level1    390, 700     level2   4315, -1200      level3 5600, -3500      level 4   1820, -3450       brain  3197, -3453      // boss3  4666, 780
    std::cout << "playerid" << playerid << std::endl;

    Audio::bootstrap();
    Font::bootstrap();

    sf::Clock clock;

    // CAMERA VIEW
    view.reset(sf::FloatRect(0, 0, WIDTH, HEIGHT));
    view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    window.setView(view);

    uiView.reset(sf::FloatRect(-2000, -2000, WIDTH, HEIGHT));
    uiView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

    sf::Text info;
    info.setFont(Font::emulogic);
    info.setCharacterSize(10);
    info.setFillColor(sf::Color::White); //5688, 490
    info.setString("");
    

    sf::Text controls;
    controls.setFont(Font::emulogic);
    controls.setCharacterSize(13);
    controls.setFillColor(sf::Color::White); //5688, 490
    controls.setString("wasd to move\ne to interact\nspace to jump\nhold shift to sprint\nnumber keys to\nchange gizmos\nleft click to fire");

    sf::Text credits;
    credits.setFont(Font::emulogic);
    credits.setCharacterSize(20);
    credits.setFillColor(sf::Color::White); //5688, 490
    credits.setPosition(5688, 490);
    credits.setString("thank you for playing my game\ni didnt have time for a proper ending\nyou get the castle and you win yada yada\ndeveloped by ben marksberry\nmusic by my best friends ian halpaus and trevor spurbeck\nmain character sprite modeled from some online template\ndeveloped for cs5732 at UMD Spring 2023");

    //AIHelper::createAI(FIREWALLGRUNT, { WIDTH / 4, HEIGHT / 2 });

    Map::load(Map::LEVEL0);


    //              TEMPORARY - NEEDS TO BE MOVED                      //

    sf::IntRect slot0 = { ((int)WIDTH / 2) - 230, 15, 100, 100 };
    sf::IntRect slot1 = { ((int)WIDTH / 2) - 115, 15, 100, 100 };
    sf::IntRect slot2 = { ((int)WIDTH / 2), 15, 100, 100 };
    sf::IntRect slot3 = { ((int)WIDTH / 2) + 115, 15, 100, 100 };

    /////////////////////////////////////////////////////////////////////




    //creating ui
    UIHealthHelper::createHealthBar(*PlayerHelper::list.at(playerid));
    UIToolboxHelper::createToolbox();
    UIInventoryHelper::createInventory();


   // auto tempDropdownPlatform = sf::RectangleShape({ 300, 10 });
    //tempDropdownPlatform.setPosition(860, 850);
    
    //PlatformHelper::createDropdownPlatform(tempDropdownPlatform);

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

        //std::cout << lerp(5000) << std::endl;
        
        controls.setPosition(window.mapPixelToCoords({ (int)WIDTH - 300, 15 }));

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
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1) {
                if (Inventory::equipItem(InventoryItem::DOSGUN)) {
                    PlayerHelper::list.at(playerid)->clock.restart();
                    info.setString("The DOS-gun\nStandard edition Denial of Service Pistol\nMaster of none");
                }
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2) {
                if (Inventory::equipItem(InventoryItem::PORTGUN)) {
                    PlayerHelper::list.at(playerid)->clock.restart();
                    info.setString("The Port Scanner\nUsed to detect hidden open ports\nGreat for breaking and entering!");
                }
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3) {
                if (Inventory::equipItem(InventoryItem::CRYPTOGUN)) {
                    PlayerHelper::list.at(playerid)->clock.restart();
                    info.setString("The Cipher\nManifests 'blobs' of highly encrypted data\nSome 'minds' might find this interesting!");
                }
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num4) {
                if (Inventory::equipItem(InventoryItem::BRUTEFORCE)) {
                    PlayerHelper::list.at(playerid)->clock.restart();
                    info.setString("Brute Force\nThe end-all to every solution\nUseful for... breaking things.");
                }
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

        auto pos = sf::Mouse::getPosition(window);
        if (slot0.contains(pos)) {
            info.setString("The DOS-gun\nStandard edition Denial of Service Pistol\nMaster of none");
            drawInfo = true;
        }
        else if (slot1.contains(pos)) {
            if (Inventory::unlockedItemList.find(InventoryItem::PORTGUN)->second == true) {
                info.setString("The Port Scanner\nUsed to detect hidden open ports or other hidden things\nTry using on an enemy\nGreat for breaking and entering!");
                drawInfo = true;
            }
            
        }
        else if (slot2.contains(pos)) {
            if (Inventory::unlockedItemList.find(InventoryItem::CRYPTOGUN)->second == true) {
                info.setString("The Cipher\nManifests 'blobs' of highly encrypted data\nTry using on an enemy\nSome 'minds' might find this interesting!");
                drawInfo = true;
            }
        }
        else if (slot3.contains(pos)) {
            if (Inventory::unlockedItemList.find(InventoryItem::BRUTEFORCE)->second == true) {
                info.setString("Brute Force\nThe end-all to every solution\nTry using on an enemy\nUseful for... breaking things.");
                drawInfo = true;
            }
        }
        else {
            drawInfo = false;
        }

        info.setPosition(window.mapPixelToCoords({ (int)WIDTH / 2 - ((int)info.getGlobalBounds().width / 2), 130 }));

        

        if (Cheats::UnlockAllGizmos) {
            Inventory::unlockItem(DOSGUN);
            Inventory::unlockItem(PORTGUN);
            Inventory::unlockItem(CRYPTOGUN);
            Inventory::unlockItem(BRUTEFORCE);
        }

        if (PlayerHelper::list.at(playerid)->health <= 0.0f) {
            EndCondition = true;
        }

        float currentTime = clock.restart().asSeconds();
        physics::dt = currentTime * 10;
        //int fps = 1.0f / currentTime;

        //std::cout << fps << std::endl;

        auto pixelpos = sf::Mouse::getPosition(window);
        auto coordpos = window.mapPixelToCoords(pixelpos);
        fpsctr.setString("X" + std::to_string(coordpos.x) + " Y" + std::to_string(coordpos.y));

        simulate();

        if (Audio::sound_grungy.getStatus() != Audio::sound_grungy.Playing && !BossEvent::inBattle) {
            //Audio::playingDefault = true;
            if (Audio::sound_grungy.getStatus() != Audio::sound_grungy.Playing) {
                Audio::sound_grungy.play();
                std::cout << Audio::sound_grungy.getStatus() << std::endl;
            }
            
            //std::cout << "shit " << std::endl;
        }

        // DRAWING
        window.draw(Map::mapSprite);

        for (auto pair : BaseObjectHelper::list) {
            auto object = pair.second;
            for (auto drawable : object->drawableList) {
                window.draw(*drawable.second);
            }

        }

        if (drawCredits) {
            window.draw(credits);
        }

        for (auto pair : InvisLayerHelper::list) {
            auto layer = pair.second;

            window.draw(layer->getSprite());
        }

        for (auto player : PlayerHelper::list) {
            window.draw(*player.second->drawable);
            window.draw(player.second->sprite);
            window.draw(player.second->chargingText);
            window.draw(player.second->scannerCircle);
        }

        if (!BossEvent::boss01.isDead()) {
            for (auto pair : BossEvent::boss01.drawableList) {
                auto sprite = pair.second;

                window.draw(*sprite);
            }
        }

        if (!BossEvent::boss02.isDead()) {
            for (auto pair : BossEvent::boss02.drawableList) {
                auto sprite = pair.second;

                window.draw(*sprite);
            }
        }

        if (!BossEvent::boss03.isDead()) {
            for (auto pair : BossEvent::boss03.drawableList) {
                auto sprite = pair.second;

                window.draw(*sprite);
            }
        }
        

        if (BossEvent::drawBossHealthbar) {
            window.draw(BossEvent::healthbar_outer);
            window.draw(BossEvent::healthbar_inner);
            window.draw(BossEvent::boss_name);
        }
        

        for (auto AI : AIHelper::list) {
            window.draw(*AI.second->drawable);
            window.draw(AI.second->sprite);
            window.draw(AI.second->healthText);
        }

        for (auto pair : PlatformHelper::list) {
            if (Cheats::DrawPlatforms) {
                auto color = pair.second->drawable->getFillColor();
                pair.second->drawable->setFillColor(sf::Color(color.r, color.g, color.b, 128));
                window.draw(*pair.second->drawable);
            }
            
        }

        for (auto pair : BulletHelper::list) {
            auto bullet = pair.second;

            //std::cout << bullet->clock.getElapsedTime().asSeconds() << std::endl;

            bool isColliding = bullet->checkForHit();
            if (signalPlayerHit && !BossEvent::boss02.isDead()) {
                BossEvent::boss02.hurtPlayer(10.f);
                signalPlayerHit = false;
            }

            if (signalPlayerHit && !BossEvent::boss03.isDead()) {
                BossEvent::boss03.hurtPlayer(10.f);
                signalPlayerHit = false;
            }

            if (!isColliding) {
                bullet->simStep(physics::dt);
                window.draw(*bullet->drawable);
            }
            else if (isColliding && bullet->doPersist && bullet->clock.getElapsedTime().asSeconds() < bullet->doPersistTime) {
                window.draw(*bullet->drawable);
            }
            else {
                BulletHelper::list.erase(bullet->id);
            }

            if ((!bullet->doPersist && bullet->clock.getElapsedTime() > sf::seconds(10)) || (bullet->doPersist && bullet->clock.getElapsedTime().asSeconds() > bullet->doPersistTime)) {
                BulletHelper::list.erase(bullet->id);
            }
        }

        window.draw(controls);
        if (drawInfo) {
            window.draw(info);
        }
        
        // DRAW UI VIEW SECTION
        UIInventoryHelper::list[0]->update(Inventory::unlockedItemList, Inventory::currentyEquippedItem);
       
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