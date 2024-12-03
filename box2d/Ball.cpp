#include "Ball.h"
#include <iostream>

Ball::Ball(b2World* world, float x, float y, const sf::Texture& texture)
{
    isNormal = true;
    // Create a Box2D body for the ball
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x / SCALE, y / SCALE);  // Convert from SFML units to Box2D units
    body = world->CreateBody(&bodyDef);

    // Create a circular shape for the ball
    b2CircleShape circleShape;
    circleShape.m_radius = 20.0f / SCALE;  // Convert radius to Box2D units

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 1.0f;   // Mass of the ball
    fixtureDef.friction = 0.3f;  // Friction coefficient
    fixtureDef.restitution = 0.6f;  // Bounciness
    body->CreateFixture(&fixtureDef);

    // Set SFML shape properties
    shape.setRadius(20.0f);
    shape.setOrigin(20.0f, 20.0f); // Center origin
    shape.setFillColor(sf::Color::White);  // Default color before texture

    // Load and apply the texture
    ballTexture = texture;  // Copy the texture
    shape.setTexture(&ballTexture);
    waveEffectActive = false;
    waveTime = 0.0f;
}
const float Ball::SCALE = 30.0f;
void Ball::update(float deltaTime) {
    // Update the position of the shape
    sf::Vector2f position(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE);
    shape.setPosition(position);

    // Get the linear velocity of the ball
    b2Vec2 velocity = body->GetLinearVelocity();
    float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);

    // Calculate rotation based on speed
    float rotationSpeed = speed * 10.0f; // Adjust multiplier as needed for desired rotation speed
    shape.rotate(rotationSpeed *0.1);

    if (waveEffectActive) {
        waveTime += deltaTime;

        if (waveTime >= 4.0f) {  // Effect lasts for 4 seconds
            waveEffectActive = false;
            shape.setScale(1.0f, 1.0f);  // Reset scale
            body->SetLinearVelocity(b2Vec2(0.0, 0));
        }
        else if (waveTime >= 0.5f) {  // Apply wave animation
            float scale = 1.0f + 0.1f * sin(waveTime * 5);
            body->SetLinearVelocity(b2Vec2(0.0, -scale));
        }
    }
}
void Ball::startWaveEffect() {
    // Trigger the wave effect when ball collides with water
    waveEffectActive = true;
    waveTime = 0.0f; // Reset the wave effect time
}
b2Vec2 Ball::GetPosition()
{
    return b2Vec2(body->GetPosition().x, body->GetPosition().y);
}
void Ball::draw(sf::RenderWindow& window) {
    window.draw(shape); // Directly draw the shape
}

void Ball::jump()
{

    b2Vec2 impulse;

    if (isMaximized) {
        impulse.Set(0.0f, -45.0f);
    }
    else if (isNormal) {
        impulse.Set(0.0f, -10.0f);
    }
    else if (isMinimized) {
        impulse.Set(0.0f, -2.0f);
    }


    body->ApplyLinearImpulseToCenter(impulse, true);
}

b2Body* Ball::getBody()
{
    return body;
}



void Ball::maximizeSize()
{
    shape.setRadius(shape.getRadius() * 2.0f);
    shape.setOrigin(shape.getRadius(), shape.getRadius());

    body->DestroyFixture(body->GetFixtureList());
    b2CircleShape newCircleShape;
    newCircleShape.m_radius = (shape.getRadius()) / SCALE;
    b2FixtureDef newFixtureDef;
    newFixtureDef.shape = &newCircleShape;
    newFixtureDef.density = 1.0f;
    newFixtureDef.friction = 0.3f;
    newFixtureDef.restitution = 0.6f;
    body->CreateFixture(&newFixtureDef);
    if (isNormal)
    {
        isMaximized = true;
        isMinimized = false;
        isNormal = false;
    }
    else {
        isNormal = true;
        isMaximized = false;
        isMinimized = false;
    }
}


void Ball::minimizeSize()
{
    shape.setRadius(shape.getRadius() * 0.5f);
    shape.setOrigin(shape.getRadius(), shape.getRadius());

    body->DestroyFixture(body->GetFixtureList());
    b2CircleShape newCircleShape;
    newCircleShape.m_radius = (shape.getRadius()) / SCALE;
    b2FixtureDef newFixtureDef;
    newFixtureDef.shape = &newCircleShape;
    newFixtureDef.density = 1.0f;
    newFixtureDef.friction = 0.3f;
    newFixtureDef.restitution = 0.6f;
    body->CreateFixture(&newFixtureDef);
    if (isNormal)
    {
        isMinimized = true;
        isMaximized = false;
        isNormal = false;
    }
    else {
        isNormal = true;
        isMinimized = false;
        isMaximized = false;
    }
}

void Ball::move(float direction)
{
    if (isMoving) {
        b2Vec2 force(10.0f * direction, 0.0f); // Force vector: positive x-direction
        body->ApplyForceToCenter(force, true);
    }
    else {
        body->ApplyForceToCenter(b2Vec2(0.0, 0.0), true);
    }

}

void Ball::setScore(int s)
{
    if (s < 0)s = 0;
    score = s;
}

int Ball::getScore()
{
    return score;
}
void Ball::setSkin(const std::string& texturePath)
{
    if (!ballTexture.loadFromFile(texturePath)) {
        std::cout << "Failed to load player texture from " << texturePath << std::endl;
        return;
    }
    shape.setTexture(&ballTexture);
    shape.setOrigin(ballTexture.getSize().x / 2.0f, ballTexture.getSize().y / 2.0f);
}