#include "MainMenu.h"

MainMenu::MainMenu(float windowWidth, float windowHeight)
{
    // Load textures
    if (!bgTexture.loadFromFile("Textures/opening.png") ||
        !playTexture.loadFromFile("Textures/PLAY.png") ||
        !levelsTexture.loadFromFile("Textures/skinBLUE.png") ||
        !exitTexture.loadFromFile("Textures/EXIT.png")) {
        std::cout << "Failed to load menu images!" << std::endl;
        return;
    }

    // Set up background
    bgSprite.setTexture(bgTexture);
    bgSprite.setScale(windowWidth / bgTexture.getSize().x, windowHeight / bgTexture.getSize().y); // Scale background to fit the window

    // Set up buttons (align to the left side)
    float buttonX = 100.0f;  // Button positions on the left
    setupButton(playButton, playTexture, buttonX, windowHeight / 2 - 60, sf::Vector2f(3.0f, 3.0f));
    setupButton(levelsButton, levelsTexture, buttonX, windowHeight / 2, sf::Vector2f(3.0f, 3.0f));
    setupButton(exitButton, exitTexture, buttonX, windowHeight / 2 + 60, sf::Vector2f(3.0f, 3.0f));

    // Load font
    if (!font.loadFromFile("Textures/Fonts/pixelfont.ttf")) {
        std::cerr << "Failed to load font\n";
        return;
    }

    // Set up title text
    titleText.setFont(font);
    titleText.setString("Bounce");
    titleText.setCharacterSize(100);
    titleText.setOutlineThickness(5);
    titleText.setOutlineColor(sf::Color::Black);
    titleText.setFillColor(sf::Color::Yellow);
    titleText.setStyle(sf::Text::Bold);
    titleText.setPosition(windowWidth / 2 - titleText.getGlobalBounds().width / 2, 50);
}

MenuOption MainMenu::handleInput(const sf::RenderWindow& window)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (playButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            std::cout << "Mouse Position: " << mousePos.x << ", " << mousePos.y << std::endl;
        std::cout << "Play Button Bounds: "
            << playButton.getGlobalBounds().left << ", "
            << playButton.getGlobalBounds().top << ", "
            << playButton.getGlobalBounds().width << ", "
            << playButton.getGlobalBounds().height << std::endl;
            return MenuOption::Play;
        }
        if (levelsButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            return MenuOption::Levels;
        }
        if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            return MenuOption::Exit;
        }
        
    }
    return MenuOption::None;
}

void MainMenu::draw(sf::RenderWindow& window)
{

    window.draw(bgSprite); // Draw the background image
    window.draw(titleText);
    window.draw(playButton);
    window.draw(levelsButton);
    window.draw(exitButton);
}

void MainMenu::setupButton(sf::Sprite& button, sf::Texture& texture, float x, float y, sf::Vector2f scale)
{

    button.setTexture(texture);
    button.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
    button.setPosition(x, y);
    button.setScale(0.1f, 0.1f);
}