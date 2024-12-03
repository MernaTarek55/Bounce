#include "Water.h"

Water::Water(b2World* world, float x, float y, float width, float height)
    : waveActive(false), waveTime(0.0f) {
    // Create a static body for the water
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(x / SCALE, y / SCALE);
    body = world->CreateBody(&bodyDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(width / 2 / SCALE, height / 2 / SCALE);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.isSensor = true; // Water acts as a sensor
    body->CreateFixture(&fixtureDef);

    // Visual representation
    waterRect.setSize(sf::Vector2f(width, height));
    waterRect.setPosition(x - width / 2, y - height / 2);
    waterRect.setFillColor(sf::Color(0, 0, 255, 128)); // Semi-transparent blue
}

void Water::startWaveEffect()
{
    printf("Ball collided with water!\n");
    waveActive = true;
    waveTime = 0.0f; // Reset wave timer
}

void Water::update(float deltaTime)
{
    if (waveActive) {
        waveTime += deltaTime;

        // Stop wave after a short duration
        if (waveTime > 4.0f) { // 2 seconds
            waveActive = false;
            waveTime = 0.0f;
        }
    }
}

//void Water::draw(sf::RenderWindow& window)
//{
//    if (waveActive) {
//        // Apply sine wave effect to the top of the rectangle
//        sf::VertexArray wave(sf::LinesStrip, 20);
//        for (size_t i = 0; i < 20; ++i) {
//            float x = waterRect.getPosition().x + (i / 19.0f) * waterRect.getSize().x;
//            float y = waterRect.getPosition().y + std::sin(waveTime * 5 + i * 0.5f) * 10; // Sine wave
//            wave[i].position = sf::Vector2f(x, y);
//            wave[i].color = sf::Color(0, 0, 255, 180);
//        }
//        window.draw(wave);
//    }
//
//    // Draw the water rectangle
//    window.draw(waterRect);
//}
void Water::draw(sf::RenderWindow& window)
{
    if (waveActive) {
        // Create a vertex array to represent the sine wave with triangles for thickness
        sf::VertexArray wave(sf::TrianglesStrip, 40);  // Increase vertex count for thickness
        for (size_t i = 0; i < 20; ++i) {
            float x = waterRect.getPosition().x + (i / 19.0f) * waterRect.getSize().x;
            float y = waterRect.getPosition().y + std::sin(waveTime * 5 + i * 0.5f) * 10; // Sine wave

            // Create two points for the thickness of the wave (increase the horizontal distance)
            float thickness = 15.0f;  // Increased thickness for a bolder wave
            wave[i * 2].position = sf::Vector2f(x - thickness, y);
            wave[i * 2 + 1].position = sf::Vector2f(x + thickness, y);
            wave[i * 2].color = sf::Color(0, 0, 255, 180);  // Color for the wave
            wave[i * 2 + 1].color = sf::Color(0, 0, 255, 180);
        }
        window.draw(wave);
    }
    window.draw(waterRect);
}