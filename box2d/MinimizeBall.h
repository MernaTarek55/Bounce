// MinimizeBall.h
#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/b2_body.h>
#include "box2d/box2d.h"
#include "Ball.h"

class MinimizeBall {
public:
    MinimizeBall(b2World* world, float x, float y, const std::string& texturePath);

    void update();
    void draw(sf::RenderWindow& window);
    void onCollision(Ball& ball); // Call minimize function on the ball
    b2Body* getBody();
    ~MinimizeBall();

private:
    b2Body* body;
    b2BodyDef bodyDef;
    sf::Sprite sprite;
    sf::Texture texture;
    const float SCALE = 30.0f;
    bool isCollected = false; // To avoid multiple collisions
};