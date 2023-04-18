#pragma once
#include "SFML/Audio.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

namespace Audio {
    sf::SoundBuffer buf_laser_00;
    sf::Sound sound_laser_00;

    sf::SoundBuffer buf_laser_01;
    sf::Sound sound_laser_01;

    sf::SoundBuffer buf_laser_02;
    sf::Sound sound_laser_02;

    sf::SoundBuffer buf_laser_03;
    sf::Sound sound_laser_03;

    sf::SoundBuffer buf_player_hurt_0_0;
    sf::Sound sound_player_hurt_0_0;

    sf::SoundBuffer buf_player_hurt_0_1;
    sf::Sound sound_player_hurt_0_1;

    sf::SoundBuffer buf_player_hurt_0_2;
    sf::Sound sound_player_hurt_0_2;
    
    sf::SoundBuffer buf_player_fall_0_0;
    sf::Sound sound_player_fall_0_0;

    sf::SoundBuffer buf_player_fall_0_1;
    sf::Sound sound_player_fall_0_1;

    void bootstrap() {
        if (!buf_laser_00.loadFromFile("Content/Audio/Blaster/laser_00.ogg")) {
            std::cout << "bad sound" << std::endl;
        }
        sound_laser_00.setBuffer(buf_laser_00);

        if (!buf_laser_01.loadFromFile("Content/Audio/Blaster/laser_01.ogg")) {
            std::cout << "bad sound" << std::endl;
        }
        sound_laser_01.setBuffer(buf_laser_01);

        if (!buf_laser_02.loadFromFile("Content/Audio/Blaster/laser_02.ogg")) {
            std::cout << "bad sound" << std::endl;
        }
        sound_laser_02.setBuffer(buf_laser_02);

        if (!buf_laser_03.loadFromFile("Content/Audio/Blaster/laser_03.ogg")) {
            std::cout << "bad sound" << std::endl;
        }
        sound_laser_03.setBuffer(buf_laser_03);

        Audio::sound_laser_00.setVolume(50);
        Audio::sound_laser_01.setVolume(50);
        Audio::sound_laser_02.setVolume(50);
        Audio::sound_laser_03.setVolume(50);

        if (!buf_player_hurt_0_0.loadFromFile("Content/Audio/Player/hurt_0_0.ogg")) {
            std::cout << "bad sound" << std::endl;
        }
        sound_player_hurt_0_0.setBuffer(buf_player_hurt_0_0);

        if (!buf_player_hurt_0_1.loadFromFile("Content/Audio/Player/hurt_0_1.ogg")) {
            std::cout << "bad sound" << std::endl;
        }
        sound_player_hurt_0_1.setBuffer(buf_player_hurt_0_1);

        if (!buf_player_hurt_0_2.loadFromFile("Content/Audio/Player/hurt_0_2.ogg")) {
            std::cout << "bad sound" << std::endl;
        }
        sound_player_hurt_0_2.setBuffer(buf_player_hurt_0_2);

        if (!buf_player_fall_0_0.loadFromFile("Content/Audio/Player/fall_0_0.ogg")) {
            std::cout << "bad sound" << std::endl;
        }
        sound_player_fall_0_0.setBuffer(buf_player_fall_0_0);

        if (!buf_player_fall_0_1.loadFromFile("Content/Audio/Player/fall_0_1.ogg")) {
            std::cout << "bad sound" << std::endl;
        }
        sound_player_fall_0_1.setBuffer(buf_player_fall_0_1);



    }


}


void playGunshot() {

    using namespace std::chrono;
    milliseconds ms = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
        );


    std::srand(ms.count()); //std::time(nullptr)
    // Generate a random number between 0 and 3
    int random_number = std::rand() % 4;

    switch (random_number) {
    case 0:
        Audio::sound_laser_00.play();
        break;
    case 1:
        Audio::sound_laser_01.play();
        break;
    case 2:
        Audio::sound_laser_02.play();
        break;
    case 3:
        Audio::sound_laser_03.play();
    }
}

void playPlayerHurt() {
    using namespace std::chrono;
    milliseconds ms = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
        );


    std::srand(ms.count()); //std::time(nullptr)
    // Generate a random number between 0 and 3
    int random_number = std::rand() % 3;

    switch (random_number) {
    case 0:
        Audio::sound_player_hurt_0_0.play();
        break;
    case 1:
        Audio::sound_player_hurt_0_1.play();
        break;
    case 2:
        Audio::sound_player_hurt_0_2.play();
        break;
    }
}

void playPlayerFall() {
    using namespace std::chrono;
    milliseconds ms = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
        );


    std::srand(ms.count()); //std::time(nullptr)
    // Generate a random number between 0 and 3
    int random_number = std::rand() % 2;

    switch (random_number) {
    case 0:
        Audio::sound_player_fall_0_0.play();
        break;
    case 1:
        Audio::sound_player_fall_0_1.play();
        break;
    }
}