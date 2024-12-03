#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

enum class Skin { Duck, Cat, Penguin , red,none };

class SkinSelector
{
public:
    SkinSelector(float windowWidth, float windowHeight);

    // Handle user input to select a skin
    Skin handleInput(const sf::RenderWindow& window);

    // Draw the skin selection window
    void draw(sf::RenderWindow& window);

private:
    sf::Texture duckTexture;
    sf::Texture catTexture;
    sf::Texture penguinTexture;
    sf::Texture redTexture;
    sf::Texture bgTexture;

    sf::Sprite duckSprite;
    sf::Sprite bgSprite;
    sf::Sprite catSprite;
    sf::Sprite penguinSprite;
    sf::Sprite redSprite;

    void setupSkin(sf::Sprite& sprite, sf::Texture& texture, const std::string& path, float x, float y);
};