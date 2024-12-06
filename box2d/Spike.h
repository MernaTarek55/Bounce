#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Spike {
public:
    Spike(b2World* world,const sf::Vector2f& position, const sf::Vector2f& size, const std::string& textureFile);
    void draw(sf::RenderWindow& window);
    b2Body* getBody() { return body; }

private:
    sf::RectangleShape shape;
    sf::Texture texture;
    b2Body* body;
};

