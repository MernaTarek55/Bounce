#include "SkinSelector.h"

SkinSelector::SkinSelector(float windowWidth, float windowHeight)
{
    if (!bgTexture.loadFromFile("Textures/sky bb.png")) { // Replace with your actual background image path
        std::cerr << "Failed to load background texture!" << std::endl;
    }
    bgSprite.setTexture(bgTexture);
    bgSprite.setScale(windowWidth / bgTexture.getSize().x, windowHeight / bgTexture.getSize().y);

    // Load textures and set up sprites for each skin
    setupSkin(duckSprite, duckTexture, "Textures/duck.png", windowWidth / 2 - 300, windowHeight / 2);
    setupSkin(catSprite, catTexture, "Textures/CATskin.png", windowWidth / 2 - 100, windowHeight / 2);
    setupSkin(penguinSprite, penguinTexture, "Textures/Ball_Peng_Skin.png", windowWidth / 2 + 100, windowHeight / 2);
    setupSkin(redSprite, redTexture, "Textures/ball final.png", windowWidth / 2 + 300, windowHeight / 2);
}

void SkinSelector::setupSkin(sf::Sprite& sprite, sf::Texture& texture, const std::string& path, float x, float y)
{
    if (!texture.loadFromFile(path)) {
        std::cerr << "Failed to load " << path << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
    sprite.setPosition(x, y);
    sprite.setScale(2.0f, 2.0f); // Scale up the sprites if needed
}

Skin SkinSelector::handleInput(const sf::RenderWindow& window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if (duckSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            return Skin::Duck;
        }
        if (catSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            return Skin::Cat;
        }
        if (penguinSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            return Skin::Penguin;
        }
        if (redSprite.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            return Skin::red;
        }
    }
    return Skin::none; // Default selection
}

void SkinSelector::draw(sf::RenderWindow& window)
{
    window.draw(bgSprite);
    window.draw(redSprite);
    window.draw(duckSprite);
    window.draw(catSprite);
    window.draw(penguinSprite);
}