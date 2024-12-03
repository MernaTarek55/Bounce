#pragma once
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <vector>
class MovingColliders {
private:
    b2Body* movObs;

    sf::RectangleShape rect;
    sf::Vector2f s;
    sf::Vector2f startPosition; // Start position as a vector
    sf::Vector2f endPosition;   // End position as a vector

    float speed;
    float rotationAngle;

    bool isMovingForward;
    bool isMovingVertical;


    sf::Texture texture;
    sf::Sprite sprite;
public:
    MovingColliders(b2World& world, sf::Vector2f startPosition, sf::Vector2f range, float speed, bool horizontal, bool vertical);
    void updateColliderX(float deltaTime);
    void updateColliderY(float deltaTime);
    void renderCollider(sf::RenderWindow& window);
};
