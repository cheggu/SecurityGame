#pragma once
#include <random>

unsigned int generateRandomNumber() {
    std::random_device rd;  // Seed for the random number generator
    std::mt19937 gen(rd());  // Standard mersenne_twister_engine
    std::uniform_int_distribution<unsigned int> dist(1, 65536);  // Range of numbers to generate

    return dist(gen);  // Generate and return a random number
}

void lerpToPosition(sf::RectangleShape& object, sf::Vector2f targetPos, float speed) {
    // Calculate the distance between the object's current position and the target position
    sf::Vector2f distance = targetPos - object.getPosition();

    // Check if the distance is less than or equal to the speed
    if (sqrt(distance.x * distance.x + distance.y * distance.y) <= speed) {
        object.setPosition(targetPos);
        return;
    }

    // Normalize the distance vector
    distance = distance / sqrt(distance.x * distance.x + distance.y * distance.y);

    // Scale the distance vector by the speed
    distance = distance * speed;

    // Add the distance vector to the object's position
    object.setPosition(object.getPosition() + distance);
}

enum direction {
    LEFT,
    RIGHT,
    DOWN,
    UP,
    NONE
};