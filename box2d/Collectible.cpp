#include "Collectible.h"
#include <iostream>
Collectible::Collectible(b2World* world, float x, float y)
{
    // Create Box2D body for the collectible
    bodyDef.type = b2_staticBody; // Static since it doesn’t move
    bodyDef.position.Set(x / SCALE, y / SCALE);
    body = world->CreateBody(&bodyDef);
    this->world = world;

    b2CircleShape shape;
    shape.m_radius = 10.0f / SCALE; // Radius in Box2D units

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.isSensor = true; // Enable sensor to detect collisions without physical response
    body->CreateFixture(&fixtureDef);

    // Load texture
    if (!texture.loadFromFile("Textures/coin.png")) {
        std::cout << "Failed to load collectible texture!" << std::endl;
        return;
    }

    // Set SFML sprite properties
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f); // Center origin
    sprite.setPosition(x, y);
}

void Collectible::update()
{
    // Update sprite position based on Box2D body
    sprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
}

void Collectible::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

b2Body* Collectible::getBody()
{
    return body;
}

void Collectible::collect()
{
    world->DestroyBody(body); // Remove the body from the physics world
    // Additional logic, e.g., increment score, can be added here
}

Collectible::~Collectible()
{
    // Destructor: Remove the body from the world when the object is destroyed
    if (body) {
        world->DestroyBody(body);
        body = nullptr;
    }
}
