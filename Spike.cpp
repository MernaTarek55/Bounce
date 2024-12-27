#include "Spike.h"
#include "Ball.h"
//Spike::Spike(b2World* world,const sf::Vector2f& position, const sf::Vector2f& size, const std::string& textureFile) {
//    
//    if (!texture.loadFromFile(textureFile)) {
//        throw std::runtime_error("Failed to load texture");
//    }
//
//    shape.setSize(size);
//
//    shape.setPosition(position);  
//    //shape.setTexture(&texture);
//    b2BodyDef bodyDef;
//    bodyDef.position.Set(position.x / Ball::SCALE, position.y / Ball::SCALE);  
//    bodyDef.type = b2_staticBody;
//
//    body = world->CreateBody(&bodyDef);
//
//    b2PolygonShape spikeShape;
//    spikeShape.SetAsBox(size.x / (2.0f * Ball::SCALE), size.y / (2.0f * Ball::SCALE)); 
//
//    b2FixtureDef fixtureDef;
//    fixtureDef.shape = &spikeShape;
//    //fixtureDef.isSensor = true;
//    body->CreateFixture(&fixtureDef);
//
//    b2Vec2 bodyPosition = body->GetPosition();
//    shape.setPosition(bodyPosition.x * Ball::SCALE, bodyPosition.y * Ball::SCALE);  
//
//}
Spike::Spike(b2World* world, const sf::Vector2f& position, const sf::Vector2f& size, const std::string& textureFile) {
    if (!texture.loadFromFile(textureFile)) {
        throw std::runtime_error("Failed to load texture");
    }

    shape.setSize(sf::Vector2f(size.x *2 , size.y*2));
    shape.setPosition(position.x - (size.x*2) / 2.0f, position.y - (size.y*2) / 2.0f);
    shape.setTexture(&texture);
    b2BodyDef bodyDef;
    bodyDef.position.Set(position.x / Ball::SCALE, position.y / Ball::SCALE);
    bodyDef.type = b2_staticBody;

    body = world->CreateBody(&bodyDef);

    b2PolygonShape spikeShape;
    spikeShape.SetAsBox((size.x-30) / (2.0f * Ball::SCALE), (size.y-30) / (2.0f * Ball::SCALE));

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &spikeShape;
    fixtureDef.isSensor = true;
    body->CreateFixture(&fixtureDef);

    b2Vec2 bodyPosition = body->GetPosition();
    
   // shape.setPosition(bodyPosition.x * Ball::SCALE - size.x / 2.0f,
     //   bodyPosition.y * Ball::SCALE - size.y / 2.0f);
}
void Spike::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

