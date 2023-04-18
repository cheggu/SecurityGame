#pragma once
#include <random>
#include <chrono>

std::vector<int> idlist = {};

unsigned int generateID() {
    auto id = idlist.size();//generateRandomNumberRange(100, 1000);
    idlist.push_back(id);
    return id;
}

unsigned int generateRandomNumberRange(int min, int max) {
    start:
    std::random_device rd;  // Seed for the random number generator
    std::mt19937 gen(rd());  // Standard mersenne_twister_engine
    std::uniform_int_distribution<unsigned int> dist(min, max);  // Range of numbers to generate

    int i = dist(gen);
    bool regen = false;

    for (auto id : idlist) {
        if (id == i) {
            regen = true;
        }
    }

    if (!regen) {
        idlist.push_back(i);
        return dist(gen);
    }
    else {
        goto start;
    }
}

unsigned int generateRandomNumber() {
    std::random_device rd;  // Seed for the random number generator
    std::mt19937 gen(rd());  // Standard mersenne_twister_engine
    std::uniform_int_distribution<unsigned int> dist(1, 262144);  // Range of numbers to generate

    return dist(gen);  // Generate and return a random number
}


enum direction {
    LEFT,
    RIGHT,
    DOWN,
    UP,
    NONE
};

