#pragma once
#include <box2d/b2_body.h>
#include "box2d/box2d.h"
#include "SFML/Graphics.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class Ball {
public:
    Ball(b2World* world, float x, float y, const sf::Texture& texture);
    void update(float deltaTime);

    void draw(sf::RenderWindow& window);

    void jump();

    b2Body* getBody();
    void maximizeSize();
    void minimizeSize();
    const static float SCALE;
    void move(float direction);
    bool isMoving = false;
    bool isMaximized = false;
    bool isMinimized = false;
    bool isNormal = false;
    void setScore(int s);
    int getScore();
    void startWaveEffect();
    b2Vec2 GetPosition();
    void setSkin(const std::string& texturePath);
private:
    b2Body* body;
    b2BodyDef bodyDef;
    sf::CircleShape shape;  // SFML representation for the circle
    int score = 0;
    bool waveEffectActive = false;
    float waveTime = 0.0f;
    sf::Texture ballTexture;
};