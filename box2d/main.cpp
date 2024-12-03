#include "Inclusion.h"
#include "Grid.h"
#include "MainMenu.h"
#include "Ball.h"
#include "Flag.h"
#include "Water.h"
#include "Collectible.h"
#include "MyContactListener.h"
#include "MovingColliders.h"


// Function to load and play background music
void playBackgroundMusic(SoundBuffer& buffer, Sound& sound) {
    if (buffer.loadFromFile("Textures/Sounds/music.mp3")) {
        sound.setBuffer(buffer);
        sound.setLoop(true); // Optional: loops the sound continuously
        sound.setVolume(10); // Set volume (adjust as needed)
        sound.play();
    }
    else {
        cerr << "Error: Could not load background music." << endl;
    }
}
MenuOption mainMenu();
std::string SelectSkin();
int main() {
    std::string t = "Textures/ball final.png";
    MenuOption option = mainMenu();
    if (option == MenuOption::Levels) {
        t = SelectSkin();
    }
    if( option == MenuOption::Exit)
        return 0;
    //sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Bounce");
    sf::View sceneView(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT)); // View for the current scene
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktopMode, "Full Grid Display", sf::Style::Fullscreen);
    sf::View view;
    view.setCenter(desktopMode.width / 2, desktopMode.height / 2);  // Center of the screen
    view.setSize(desktopMode.width, desktopMode.height);            // Match the full screen size
    window.setView(view);
    //window.setView(sceneView);

    int cellSizeX = WINDOW_WIDTH / SCENE_WIDTH;  // Grid cell width
    int cellSizeY = WINDOW_HEIGHT / SCENE_HEIGHT; // Grid cell height

    // Initialize Box2D world with gravity
    b2Vec2 gravity(0.0f, 9.8f);
    b2World world(gravity);

    // Load the grid and textures
    Grid gridMap;
    std::vector<Position> emptyPositions;
    std::vector<std::vector<char>> levelGrid;
    SoundBuffer buffer;
    Sound sound;
    playBackgroundMusic(buffer, sound);
    gridMap.loadGrid("gridTest.txt", levelGrid, emptyPositions);

    std::vector<std::string> texturePaths = {
        "Textures/TILE BRICK ground.png", "Textures/TILE BRICK wo ground.png",
        "Textures/TILE BRICK ground tilt.png", "Textures/TILE BRICK jump.png",
        "Textures/sky bb.png", "Textures/flag.png", "Textures/Hole.png",
        "Textures/Pillar.png", "Textures/gate.png", "Textures/size up.png",
        "Textures/Spike.png", "Textures/star.png", "Textures/heart-HP.png",
        "Textures/coin.png", "Textures/TILE BRICK wo ground tilt fill.png",
        "Textures/ball final.png", "Textures/cracked ball FINAL.png",
        "Textures/TILE BRICK wo ground tilt fill.png", "Textures/TILEBRICKwogroundtiltupside.png",
        "Textures/monster1.png", "Textures/TILEBRICKwogroundtiltfill.png",
        "Textures/TILE BRICK wo ground wo grass.png", "Textures/TILEBRICKwogroundtiltupsidegrass.png",
        "Textures/TILE BRICK ground tilt opposite.png"
    };

    //sf::Texture backgroundTexture;
    //if (!backgroundTexture.loadFromFile("Textures/sky bb.png")) {
    //    std::cerr << "Error: Could not load background texture." << std::endl;
    //    return EXIT_FAILURE;
    //}
    //sf::Sprite backgroundSprite;
    //backgroundSprite.setTexture(backgroundTexture);

    //// Scale the background to fit the entire window
    //backgroundSprite.setScale(
    //    static_cast<float>(WINDOW_WIDTH) / backgroundTexture.getSize().x,
    //    static_cast<float>(WINDOW_HEIGHT) / backgroundTexture.getSize().y
    //);
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    backgroundTexture.loadFromFile("Textures/sky bb.png");
    backgroundSprite.setTexture(backgroundTexture);

    // Get the window size and scale the background
    sf::Vector2u windowSize = window.getSize();
    backgroundSprite.setScale(
        windowSize.x / backgroundTexture.getSize().x,
        windowSize.y / backgroundTexture.getSize().y
    );

    // Assume each cell in the grid has a sprite or character
    int cellWidth = 32;  // Width of each cell in the grid
    int cellHeight = 32; // Height of each cell in the grid

    if (!gridMap.loadTextures(texturePaths)) {
        return EXIT_FAILURE;
    }

    gridMap.initializePhysics(world, levelGrid, cellSizeX, cellSizeY);

    //sf::Texture& backgroundTexture = gridMap.getTexture(4);
    //std::cout << "Texture size: "
    //    << backgroundTexture.getSize().x << " x "
    //    << backgroundTexture.getSize().y << std::endl;

    //sf::Sprite background;
    //background.setTexture(backgroundTexture);
    //background.setScale(
    //    static_cast<float>(WINDOW_WIDTH) / backgroundTexture.getSize().x,
    //    static_cast<float>(WINDOW_HEIGHT) / backgroundTexture.getSize().y
    //);

    // Use texture 15 for the player
    sf::Texture* playerTexture = &gridMap.getTexture(15);
    sf::CircleShape playerCircle(15.0f); // Radius in pixels
    playerCircle.setTexture(playerTexture);
    playerCircle.setOrigin(15.0f, -15.0f); // Center origin
    sf::Texture ballTexture;
    if (!ballTexture.loadFromFile(t)) {
        // Handle error
    }

    // Create a ball object
    Ball ball(&world, 80, 150, ballTexture);
    Flag flag(&world, 1000.0f, 800.0f, 100.0f, 100.0f, "Textures/flag.png");
    Water water(&world, 529, 1050, 262, 500);
    // Create the player's dynamic circle body in Box2D

    MovingColliders collider(world, sf::Vector2f(22.5f, 25.0f), sf::Vector2f(5.0f, 0.0f), 1.0f, true, false);
    MovingColliders collider2(world, sf::Vector2f(25.0f, 20.0f), sf::Vector2f(0.0f, 4.f), 1.0f, false, true);

    std::vector<Collectible*> collectibles;
    collectibles.push_back(new Collectible(&world, 200, 200));
    collectibles.push_back(new Collectible(&world, 850, 400));
    std::vector<MaximizeBall*> maximizeBalls;
    maximizeBalls.push_back(new MaximizeBall(&world, 300, 200, "Textures/size up.png"));

    std::vector<MinimizeBall*> minimizeBalls;
    minimizeBalls.push_back(new MinimizeBall(&world, 400, 200, "Textures/size down.png"));

    std::vector<MaximizeBall*> toRemoveMax;
    std::vector<MinimizeBall*> toRemoveMin;
    // List for removal
    std::vector<Collectible*> toRemove;
    bool isJumping = false;
    MyContactListener contactListener(ball, collectibles, toRemove, isJumping, water, flag, maximizeBalls, minimizeBalls, toRemoveMax, toRemoveMin);
    int currentSceneX = 0; // Current scene X index
    int currentSceneY = 0; // Current scene Y index
    int currentScene = 0;
    world.SetContactListener(&contactListener);
    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::Space && !isJumping) {
                    isJumping = true;
                    ball.jump();
                }
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::D) {
                    ball.isMoving = true;
                    ball.move(1);
                }
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::A) {
                    ball.isMoving = true;
                    ball.move(-1);
                }
                if (event.type == Event::KeyPressed && (event.key.code == Keyboard::D || event.key.code == Keyboard::A)) {
                    ball.isMoving = false;
                }
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::X && !ball.isMaximized) {

                    if (ball.isNormal)
                        ball.maximizeSize();
                    else {
                        ball.maximizeSize();
                        ball.isNormal = true;
                        ball.isMaximized = false;
                        ball.isMinimized = false;
                    }
                }
                if (event.type == Event::KeyPressed && event.key.code == Keyboard::N && !ball.isMinimized) {
                    if (ball.isNormal)
                        ball.minimizeSize();
                    else {
                        ball.minimizeSize();
                        ball.isNormal = true;
                        ball.isMinimized = false;
                        ball.isMaximized = false;
                    }
                }
            }
            switch (event.key.code) {
            case sf::Keyboard::Num1:
                currentScene = 0; // Full view
                break;
            case sf::Keyboard::Num2:
                currentScene = 1; // Vertical split
                break;
            case sf::Keyboard::Num3:
                currentScene = 2; // Four quadrants
                break;
            case sf::Keyboard::Num4:
                currentScene = 3; // Player-focused
                break;
            case sf::Keyboard::Num5:
                currentScene = 3; // Player-focused
                break;
            default:    
                break;
            }

            gridMap.switchView(window, sceneView, currentScene, ball.GetPosition());
            if (event.type == sf::Event::Resized) {
                float newWidth = static_cast<float>(event.size.width);
                float newHeight = static_cast<float>(event.size.height);

                float aspectRatio = newWidth / newHeight;

                if (aspectRatio > WINDOW_WIDTH / WINDOW_HEIGHT) {
                    float newViewWidth = WINDOW_HEIGHT * aspectRatio;
                    sceneView.setSize(newViewWidth, WINDOW_HEIGHT);
                }
                else {
                    float newViewHeight = WINDOW_HEIGHT / aspectRatio;
                    sceneView.setSize(WINDOW_HEIGHT, newViewHeight);
                }

                window.setView(view);
            }
        }
        for (auto& m : maximizeBalls) {
            m->update();
        }
        for (auto& m : minimizeBalls) {
            m->update();
        }
        // Remove collected collectibles
        for (auto* m : toRemoveMax) {
            maximizeBalls.erase(std::remove(maximizeBalls.begin(), maximizeBalls.end(), m), maximizeBalls.end());
            delete m; // Free memory
            ball.maximizeSize();
        }
        toRemoveMax.clear();
        for (auto* m : toRemoveMin) {
            minimizeBalls.erase(std::remove(minimizeBalls.begin(), minimizeBalls.end(), m), minimizeBalls.end());
            delete m; // Free memory
            ball.minimizeSize();
        }
        toRemoveMax.clear();
        toRemoveMin.clear();
        world.Step(1.0f / 60.0f, 6, 2);
        collider.updateColliderX(deltaTime);
        collider2.updateColliderY(deltaTime);

        int playerSceneX = playerCircle.getPosition().x / (SCENE_WIDTH * cellSizeX);
        int playerSceneY = playerCircle.getPosition().y / (SCENE_HEIGHT * cellSizeY);

        if (playerSceneX >= 0 && playerSceneX < (levelGrid[0].size() / SCENE_WIDTH) &&
            playerSceneY >= 0 && playerSceneY < (levelGrid.size() / SCENE_HEIGHT)) {
            // Update current scene and view
            currentSceneX = playerSceneX;
            currentSceneY = playerSceneY;
            sceneView.setCenter(currentSceneX * WINDOW_WIDTH + WINDOW_WIDTH / 2,
                currentSceneY * WINDOW_HEIGHT + WINDOW_HEIGHT / 2);
            window.setView(view);
        }
        ball.update(deltaTime);
        water.update(deltaTime);
        flag.update();
        for (auto& collectible : collectibles) {
            collectible->update();
        }
        

        // Remove collected collectibles
        for (auto& collectible : toRemove) {
            collectibles.erase(std::remove(collectibles.begin(), collectibles.end(), collectible), collectibles.end());
            delete collectible; // Free memory
            ball.setScore(ball.getScore() + 1);
        }
        toRemove.clear();

        // Render everything
        window.clear();
        
        window.draw(backgroundSprite);
        water.draw(window);
        gridMap.drawWalls(window, levelGrid, cellSizeX, cellSizeY, sceneView);
        for (auto& collectible : collectibles) {
            collectible->draw(window);
        }
        collider.renderCollider(window);
        collider2.renderCollider(window);
        for (auto& maximizeBall : maximizeBalls) {
            maximizeBall->update();
            maximizeBall->draw(window);
        }
        for (auto& minimizeBall : minimizeBalls) {
            minimizeBall->update();
            minimizeBall->draw(window);
        }
        flag.draw(window);
        ball.draw(window);
        window.display();
    }

    return EXIT_SUCCESS;
}