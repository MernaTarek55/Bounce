#pragma once
#include <box2d/b2_body.h>
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
class Collectible
{
public:
    Collectible(b2World* world, float x, float y);

    void update();

    void draw(sf::RenderWindow& window);

    b2Body* getBody();

    void collect();

    ~Collectible();
private:
    b2World* world;
    b2Body* body;
    b2BodyDef bodyDef;
    sf::CircleShape sfShape;
    const float SCALE = 30.0f;
    sf::Texture texture;
    sf::Sprite sprite;
};

    