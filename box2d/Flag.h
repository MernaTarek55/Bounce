#pragma once
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Flag {
private:
    b2Body* body;               // Box2D body for the flag
    sf::Sprite sprite;          // SFML sprite for visual representation
    sf::Texture texture;        // Texture for the flag image
    bool isColliding;           // Flag to track collision state
    int checkpointCount;
    sf::RectangleShape debugShape;
    float posx, posy;
public:
    Flag(b2World* world, float x, float y, float width, float height, const std::string& texturePath);
    void update();
    void draw(sf::RenderWindow& window);
    void onCollision();         // Triggered on collision
    b2Body* getBody();
    sf::Vector2f getposition();

};

