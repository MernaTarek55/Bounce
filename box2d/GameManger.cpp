#include "MainMenu.h"
#include "SkinSelector.h"
#include "Ball.h"
#include <iostream>
MenuOption mainMenu() {
    const float windowWidth = 800.0f;
    const float windowHeight = 600.0f;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Main Menu");

    MainMenu menu(windowWidth, windowHeight);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Handle menu interactions
        MenuOption selectedOption = menu.handleInput(window);
        if (selectedOption == MenuOption::Play) {
            return MenuOption::Play;
            std::cout << "Play selected!" << std::endl;
            // Transition to the play state
        }
        else if (selectedOption == MenuOption::Levels) {
            return MenuOption::Levels;
            std::cout << "Levels selected!" << std::endl;
            // Transition to the levels selection state
        }
        else if (selectedOption == MenuOption::Exit) {
            return MenuOption::Exit;
            std::cout << "Exit selected!" << std::endl;
            window.close();
        }

        // Render the menu
        window.clear();
        menu.draw(window);
        window.display();
    }
    return  MenuOption::None;
}
std::string SelectSkin() {
    std::string t;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Skin Selector");
    SkinSelector skinSelector(800, 600);

    Skin selectedSkin = Skin::Duck; // Default skin

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        // Draw the skin selection UI
        skinSelector.draw(window);
        window.display();
        // Handle input to select a skin
        selectedSkin = skinSelector.handleInput(window);

        // Apply the selected skin to the player
        switch (selectedSkin) {
        case Skin::Duck:
            t = "Textures/duck.png";
            window.close();
            break;
        case Skin::Cat:
            t = "Textures/CATskin.png";
            window.close();
            break;
        case Skin::Penguin:
            t = "Textures/Ball_Peng_Skin.png";
            window.close();
            break;
        case Skin::red:
            t = "Textures/ball final.png";
            window.close();
            break;
        case Skin::none:
            break;
        }

        
       
    }
    printf("",t);
    return t;
}