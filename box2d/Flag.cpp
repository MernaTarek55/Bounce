#include "Flag.h"
#include <iostream>
#include "Ball.h"

Flag::Flag(b2World* world, float x, float y, float width, float height, const std::string& texturePath)
    : isColliding(false) {
    // Load the texture
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
    }

    // Set up the sprite
    sprite.setTexture(texture);
    sprite.setOrigin(width / 2, height / 2);
    sprite.setPosition(x, y);

    // Scale the sprite to match the size
    sprite.setScale(width / texture.getSize().x, height / texture.getSize().y);

    // Create Box2D body
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set((x - 125) / Ball::SCALE, y / Ball::SCALE);  // Position in Box2D units
    body = world->CreateBody(&bodyDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox((width - 120) / Ball::SCALE, (height + 100) / Ball::SCALE);  // Half dimensions in Box2D units

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.isSensor = true;  // Flag should act as a sensor
    body->CreateFixture(&fixtureDef);

    // Red outline for debugging

   // Debug output
    //printf("Flag Body Position: %.2f, %.2f\n", body->GetPosition().x, body->GetPosition().y);
}

void Flag::update() {
    // Align debug shape with the Box2D body
    b2Vec2 bodyPos = body->GetPosition();
    //    debugShape.setPosition(bodyPos.x * Ball::SCALE, bodyPos.y * Ball::SCALE);  // Convert Box2D position to SFML units

    //printf("Flag Body Position: %.2f, %.2f | Debug Shape Position: %.2f, %.2f\n",
       // body->GetPosition().x, body->GetPosition().y,
       // debugShape.getPosition().x, debugShape.getPosition().y);

    if (isColliding) {
        sprite.setScale(sprite.getScale().x, sprite.getScale().y + 0.2f);  // Adjust scale on collision
        isColliding = false;  // Reset collision flag
        checkpointCount++;
    }
}

void Flag::draw(sf::RenderWindow& window) {
    window.draw(sprite);       // Draw the sprite
    window.draw(debugShape);   // Draw the debug shape
}

void Flag::onCollision() {
    if (checkpointCount == 0) {
        isColliding = true;  // Set the collision flag
    }
}

b2Body* Flag::getBody() {
    return body;
}
