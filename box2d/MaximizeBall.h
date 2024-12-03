#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/b2_body.h>
#include "box2d/box2d.h"
#include "Ball.h"
class MaximizeBall
{
public:
    MaximizeBall(b2World* world, float x, float y, const std::string& texturePath);

    void update();
    void draw(sf::RenderWindow& window);
    void onCollision(Ball& ball); // Call max function on the ball
    b2Body* getBody();
    ~MaximizeBall();

private:
    b2Body* body;
    b2BodyDef bodyDef;
    sf::Sprite sprite;
    sf::Texture texture;
    const float SCALE = 30.0f;
    bool isCollected = false; // To avoid multiple collisions
};