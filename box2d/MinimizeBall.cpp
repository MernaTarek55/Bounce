// MinimizeBall.cpp
#include "MinimizeBall.h"
#include <iostream>

MinimizeBall::MinimizeBall(b2World* world, float x, float y, const std::string& texturePath) {
    // Create Box2D body
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(x / SCALE, y / SCALE);
    body = world->CreateBody(&bodyDef);

    b2CircleShape shape;
    shape.m_radius = 15.0f / SCALE;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.isSensor = true; // Trigger collisions without physical response
    body->CreateFixture(&fixtureDef);

    // Load texture for icon
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load MinimizeBall texture!" << std::endl;
    }

    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
    sprite.setPosition(x, y);
    //sprite.setScale(0.5f, 0.5f); // Adjust size
}

void MinimizeBall::update() {
    if (!isCollected) {
        sprite.setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
    }
}

void MinimizeBall::draw(sf::RenderWindow& window) {
    if (!isCollected) {
        window.draw(sprite);
    }
}

void MinimizeBall::onCollision(Ball& ball) {
    if (!isCollected) {
        ball.minimizeSize(); // Call minimize function on ball
        isCollected = true; // Prevent further collisions
    }
}

b2Body* MinimizeBall::getBody()
{
    return body;
}

MinimizeBall::~MinimizeBall() {
    if (body) {
        body->GetWorld()->DestroyBody(body);
        body = nullptr;
    }
}