#include "MovingColliders.h"
#include "Ball.h"

MovingColliders::MovingColliders(b2World& world, sf::Vector2f startPosition, sf::Vector2f range, float speed, bool horizontal, bool vertical)
    : startPosition(startPosition),
    endPosition(startPosition + range),
    speed(speed),
    isMovingForward(horizontal),
    isMovingVertical(vertical),
    rotationAngle(0.0f) {
    // Define the body
    b2BodyDef bodyDef;
    bodyDef.type = b2_kinematicBody; // Kinematic for controlled movement
    bodyDef.position.Set(startPosition.x, startPosition.y);
    movObs = world.CreateBody(&bodyDef);

    // Define the shape
    b2PolygonShape boxShape;
    boxShape.SetAsBox(1.0f, 1.0f); // Collider dimensions

    // Define the fixture
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;

    movObs->CreateFixture(&fixtureDef);
    // Initialize SFML rectangle for visualization
    s.x = 10.0;
    s.y = 10.0;
    rect.setSize(sf::Vector2f(s.x * 30.f, s.y * 30.f));
    rect.setOrigin(s.x * 15.f, s.y * 15.f); // Adjust origin
    rect.setFillColor(sf::Color::Blue);

    // Load texture
    if (!texture.loadFromFile("Textures/monster1.png")) {
        throw std::runtime_error("Failed to load monster1.png");
    }

    // Setup sprite
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
    //sprite.setScale(s.x * 30.f / texture.getSize().x, s.y * 30.f / texture.getSize().y);
}

void MovingColliders::updateColliderX(float deltaTime) {
    b2Vec2 position = movObs->GetPosition();

    if (isMovingForward) {
        position.x += speed * deltaTime;
        if (position.x >= endPosition.x) {
            position.x = endPosition.x;
            isMovingForward = false;
        }
    }
    else {
        position.x -= speed * deltaTime;
        if (position.x <= startPosition.x) {
            position.x = startPosition.x;
            isMovingForward = true;
        }
    }

    movObs->SetTransform(position, movObs->GetAngle());
}

void MovingColliders::updateColliderY(float deltaTime) {

    b2Vec2 position = movObs->GetPosition();

    if (isMovingForward) {
        position.y += speed * deltaTime;
        if (position.y >= endPosition.y) {
            position.y = endPosition.y;
            isMovingForward = false;
        }
    }
    else {
        position.y -= speed * deltaTime;
        if (position.y <= startPosition.y) {
            position.y = startPosition.y;
            isMovingForward = true;
        }
    }

    movObs->SetTransform(position, movObs->GetAngle());
}


void MovingColliders::renderCollider(sf::RenderWindow& window) {
    // Increment rotation angle for continuous rotation
    rotationAngle += 1.0f; // Adjust the increment value for different rotation speeds
    if (rotationAngle >= 360.0f) {
        rotationAngle -= 360.0f; // Keep the angle within 0-360 degrees
    }

    // Get the Box2D body's position
    b2Vec2 position = movObs->GetPosition();

    // Update the sprite's position and rotation
    sprite.setPosition(position.x * Ball::SCALE, position.y * Ball::SCALE);
    sprite.setRotation(rotationAngle);

    // Optionally draw the rectangle for debugging purposes
    sf::RectangleShape movObsRec(sf::Vector2f(20.0f, 20.0f));
    movObsRec.setOrigin(10.0f, 10.0f);
    movObsRec.setPosition(position.x * Ball::SCALE, position.y * Ball::SCALE);
    movObsRec.setRotation(rotationAngle);
    movObsRec.setFillColor(sf::Color::Transparent); // Make it transparent if only for debugging

    // Draw the sprite
    window.draw(sprite);


}
