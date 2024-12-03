#pragma once
#include <box2d/b2_body.h>
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
class Water {
public:
    Water(b2World* world, float x, float y, float width, float height);
    void startWaveEffect();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    b2Body* getBody() { return body; }

private:
    b2Body* body;
    sf::RectangleShape waterRect;
    sf::RectangleShape redBox;
    bool waveActive;
    float waveTime;

    const float SCALE = 30.0f; // Define scaling factor
};