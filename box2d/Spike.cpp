#include "Spike.h"
#include "Ball.h"
Spike::Spike(b2World* world,const sf::Vector2f& position, const sf::Vector2f& size, const std::string& textureFile) {
    // Load the texture
    if (!texture.loadFromFile(textureFile)) {
        throw std::runtime_error("Failed to load texture");
    }

    // Set up the shape
    shape.setSize(size);

    shape.setPosition(position);  // In pixels (SFML)
    shape.setTexture(&texture);
    // Create Box2D body (static body for spike)
    b2BodyDef bodyDef;
    bodyDef.position.Set(position.x / Ball::SCALE, position.y / Ball::SCALE);  // Convert to Box2D scale
    bodyDef.type = b2_staticBody;

    body = world->CreateBody(&bodyDef);

    // Attach fixture to make it collidable
    b2PolygonShape spikeShape;
    spikeShape.SetAsBox(size.x / (2.0f * Ball::SCALE), size.y / (2.0f * Ball::SCALE));  // Convert size

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &spikeShape;
    fixtureDef.isSensor = true;
    body->CreateFixture(&fixtureDef);

    // In the game loop, update sprite position based on Box2D body position
    b2Vec2 bodyPosition = body->GetPosition();
    shape.setPosition(bodyPosition.x * Ball::SCALE, bodyPosition.y * Ball::SCALE);  // Convert back to pixels

}

void Spike::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

