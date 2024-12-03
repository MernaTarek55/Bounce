#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>
#include <iostream>

enum class MenuOption {
    None,
    Play,
    Levels,
    Exit
};

class MainMenu {
public:
    MainMenu(float windowWidth, float windowHeight);
    MenuOption handleInput(const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

private:
    void setupButton(sf::Sprite& button, sf::Texture& texture, float x, float y, sf::Vector2f scale);

    sf::Texture playTexture;
    sf::Texture levelsTexture;
    sf::Texture exitTexture;
    sf::Texture bgTexture;

    sf::Sprite playButton;
    sf::Sprite levelsButton;
    sf::Sprite exitButton;
    sf::Sprite bgSprite;

    sf::Font font;
    sf::Text titleText;
};

#endif
