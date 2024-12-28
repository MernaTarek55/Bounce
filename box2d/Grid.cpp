#include "Grid.h"
int cellSizeX = WINDOW_WIDTH /*/ SCENE_WIDTH*/;  // Grid cell width
int cellSizeY = WINDOW_HEIGHT /*/ SCENE_HEIGHT*/; // Grid cell height
void Grid::loadGrid(const std::string& path, std::vector<std::vector<char>>& grid, std::vector<Position>& emptyPositions) {
    std::ifstream myfile(path, std::ios_base::in);

    if (!myfile.is_open()) {
        std::cerr << "Error: Could not open file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(myfile, line)) {
        std::vector<char> row(line.begin(), line.end());
        grid.push_back(row);
    }

    myfile.close();
}

bool Grid::loadTextures(const std::vector<std::string>& texturePaths) {
    if (texturePaths.size() != 24) {
        std::cerr << "Error: Expected 24 texture paths, got " << texturePaths.size() << std::endl;
        return false;
    }

    for (size_t i = 0; i < texturePaths.size(); ++i) {
        if (!textures[i].loadFromFile(texturePaths[i])) {
            std::cerr << "Error: Could not load texture file: " << texturePaths[i] << std::endl;
            return false;
        }
    }

    charToTextureIndex = {
        {'X', 0}, {'Z', 1}, {'C', 2}, {'S', 3}, // Wall, Ground, Slide, Bouncer
        {'1', 4}, {'2', 5}, {'3', 6}, {'4', 7}, // Sky, Flag, Hole, Plank
        {'5', 8}, {'6', 9}, {'7', 10}, {'8', 11}, // Ring, Size Up, Spike, Star
        {'9', 12}, {'E', 13}, {'Y', 14}, {'T', 15}, // Heart, Coin, Ball
        {'W', 16}, {'U', 17}, {'V', 18}, {'G', 19}, {'H', 20}, // Additional tiles
        {'P', 21 }, {'I', 22}, {'O', 23}
    };

    return true;
}

sf::Texture& Grid::getTexture(int index) {
    return textures[index];
}

void Grid::initializePhysics(b2World& world, const std::vector<std::vector<char>>& grid, int cellSizeXX, int cellSizeYY) {
    for (size_t row = 0; row < grid.size(); ++row) {
        for (size_t col = 0; col < grid[row].size(); ++col) {
            char gridChar = grid[row][col];

            // Create Box2D body for specific characters
            if (gridChar == 'X' || gridChar == 'Z') {
                b2BodyDef bodyDef;
                bodyDef.position.Set(col * (float)cellSizeXX / SCALE, row * (float)cellSizeYY / SCALE);
                bodyDef.type = b2_staticBody;

                b2PolygonShape groundShape;
                groundShape.SetAsBox(0.5f * cellSizeXX / SCALE, 0.5f * cellSizeYY / SCALE);

                b2Body* groundBody = world.CreateBody(&bodyDef);
                groundBody->CreateFixture(&groundShape, 0.0f);
            }

            else if (gridChar == 'C') {
                b2BodyDef bodyDef;
                bodyDef.position.Set(col * (float)cellSizeXX / SCALE, row * (float)cellSizeYY / SCALE);
                bodyDef.type = b2_staticBody;

                // Define a triangular shape with the vertices top-left, bottom-left, bottom-right
                b2PolygonShape triangleShape;
                b2Vec2 vertices[3]; // Three vertices for a triangle

                vertices[0].Set(0.0f, 0.0f);                           // Top-left (origin)
                vertices[1].Set(0.0f, cellSizeYY / SCALE);             // Bottom-left
                vertices[2].Set(cellSizeXX / SCALE, cellSizeYY / SCALE); // Bottom-right

                triangleShape.Set(vertices, 3); // Set the triangle shape

                b2Body* triangleBody = world.CreateBody(&bodyDef);
                triangleBody->CreateFixture(&triangleShape, 0.0f);
            }


            //// Create concave shapes for 'C' and 'O'
            //else if (gridChar == 'C' || gridChar == 'O') {
            //    b2BodyDef bodyDef;
            //    bodyDef.position.Set(col * (float)cellSizeXX / SCALE, row * (float)cellSizeYY / SCALE);
            //    bodyDef.type = b2_staticBody;

            //    b2PolygonShape concaveShape;
            //    b2Vec2 vertices[4];

            //    if (gridChar == 'C') {
            //        // Define a concave shape for 'C'
            //        vertices[0].Set(-0.5f * cellSizeXX / SCALE, -0.5f * cellSizeYY / SCALE);
            //        vertices[1].Set(0.5f * cellSizeXX / SCALE, -0.5f * cellSizeYY / SCALE);
            //        vertices[2].Set(0.0f * cellSizeXX / SCALE, 0.5f * cellSizeYY / SCALE);
            //        vertices[3].Set(-0.5f * cellSizeXX / SCALE, 0.5f * cellSizeYY / SCALE);
            //    }
            //    else if (gridChar == 'O') {
            //        // Define a concave shape for 'O'
            //        vertices[0].Set(-0.5f * cellSizeXX / SCALE, -0.5f * cellSizeYY / SCALE);
            //        vertices[1].Set(0.5f * cellSizeXX / SCALE, -0.5f * cellSizeYY / SCALE);
            //        vertices[2].Set(0.5f * cellSizeXX / SCALE, 0.5f * cellSizeYY / SCALE);
            //        vertices[3].Set(-0.5f * cellSizeXX / SCALE, 0.0f * cellSizeYY / SCALE);
            //    }

            //    concaveShape.Set(vertices, 4);
            //    b2Body* concaveBody = world.CreateBody(&bodyDef);
            //    concaveBody->CreateFixture(&concaveShape, 0.0f);
            //}
        }
    }
}

void Grid::drawWalls(sf::RenderWindow& window, const std::vector<std::vector<char>>& grid, int cellSizeXX, int cellSizeYY, sf::View& view) {
    sf::Vector2f center = view.getCenter();
    sf::Vector2f size = view.getSize();

    int startRow = std::max(0, static_cast<int>((center.y - size.y / 2) / cellSizeYY));
    int endRow = std::min(static_cast<int>(grid.size()), static_cast<int>((center.y + size.y / 2) / cellSizeYY) + 1);
    int startCol = std::max(0, static_cast<int>((center.x - size.x / 2) / cellSizeXX));
    int endCol = std::min(static_cast<int>(grid[0].size()), static_cast<int>((center.x + size.x / 2) / cellSizeXX) + 1);

    for (int row = startRow; row < endRow; ++row) {
        for (int col = startCol; col < endCol; ++col) {
            char gridChar = grid[row][col];
            if (charToTextureIndex.find(gridChar) != charToTextureIndex.end()) {
                int textureIndex = charToTextureIndex[gridChar];

                if (textureIndex >= 0 && textureIndex < 24) {
                    sf::RectangleShape cell(sf::Vector2f(cellSizeXX, cellSizeYY));
                    cell.setOrigin(cell.getSize().x / 2, cell.getSize().y / 2);
                    cell.setPosition(col * cellSizeXX, row * cellSizeYY);

                    cell.setTexture(&textures[textureIndex]);
                    window.draw(cell);
                }
            }
        }
    }
}

//void Grid::drawWalls(sf::RenderWindow& window, const std::vector<std::vector<char>>& grid, int cellSizeX, int cellSizeY, sf::View& view) {
//    // Ensure full grid scaling
//    sf::Vector2f center = view.getCenter();
//    sf::Vector2f size = view.getSize();
//
//    for (size_t row = 0; row < grid.size(); ++row) {
//        for (size_t col = 0; col < grid[row].size(); ++col) {
//            sf::RectangleShape cell(sf::Vector2f(cellSizeX, cellSizeY));
//            cell.setPosition(col * cellSizeX, row * cellSizeY);
//
//            char gridChar = grid[row][col];
//            if (charToTextureIndex.find(gridChar) != charToTextureIndex.end()) {
//                int textureIndex = charToTextureIndex[gridChar];
//                cell.setTexture(&textures[textureIndex]);
//
//                // Scale texture to fit the cell
//                sf::Vector2u textureSize = textures[textureIndex].getSize();
//                float scaleX = static_cast<float>(cellSizeX) / textureSize.x;
//                float scaleY = static_cast<float>(cellSizeY) / textureSize.y;
//                cell.setTextureRect(sf::IntRect(0, 0, textureSize.x, textureSize.y));
//                cell.setScale(scaleX, scaleY);
//            }
//
//            window.draw(cell);
//        }
//    }
//}

//void Grid::switchView(sf::RenderWindow& window, sf::View& view, int scene, const b2Vec2& playerCircle) {
//    sf::Vector2f playerPosition(playerCircle.x, playerCircle.y);
//
//    // Get the full screen resolution
//    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
//    int fullGridHeight, fullGridWidth, gridHeight, gridWidth;
//    switch (scene) {
//    case 0: // Full grid view
//        // Set the view to display the entire grid
//        // Calculate grid dimensions
//        gridWidth = sizeof(grid[0]) / sizeof(grid[0][0]); // 48 columns
//        gridHeight = sizeof(grid) / sizeof(grid[0]);      // 15 rows
//
//        // You can use these dimensions for full grid calculation
//        fullGridWidth = gridWidth * cellSizeX;
//        fullGridHeight = gridHeight * cellSizeY;
//
//        // Center the view and adjust size to fit the full grid on the screen
//        view.setCenter(fullGridWidth / 2, fullGridHeight / 2);
//        view.setSize(fullGridWidth, fullGridHeight);
//        break;
//
//    case 1: // Vertical split
//        if (playerPosition.x < desktopMode.width / 2) {
//            view.setCenter(desktopMode.width / 4, desktopMode.height / 2);
//        }
//        else {
//            view.setCenter(3 * desktopMode.width / 4, desktopMode.height / 2);
//        }
//        view.setSize(desktopMode.width / 2, desktopMode.height);
//        break;
//
//    case 2: // Four quadrants
//        if (playerPosition.x < desktopMode.width / 2) {
//            if (playerPosition.y < desktopMode.height / 2) {
//                view.setCenter(desktopMode.width / 4, desktopMode.height / 4); // Top-left quadrant
//            }
//            else {
//                view.setCenter(desktopMode.width / 4, 3 * desktopMode.height / 4); // Bottom-left quadrant
//            }
//        }
//        else {
//            if (playerPosition.y < desktopMode.height / 2) {
//                view.setCenter(3 * desktopMode.width / 4, desktopMode.height / 4); // Top-right quadrant
//            }
//            else {
//                view.setCenter(3 * desktopMode.width / 4, 3 * desktopMode.height / 4); // Bottom-right quadrant
//            }
//        }
//        view.setSize(desktopMode.width / 2, desktopMode.height / 2);
//        break;
//
//    case 3: // Player-focused view
//        view.setCenter(playerPosition.x, playerPosition.y);
//        view.setSize(player_Scene_WIDTH * SCALE, player_Scene_HEIGHT * SCALE);
//        break;
//
//    default:
//        std::cerr << "Invalid scene index." << std::endl;
//        break;
//    }
//
//    window.setView(view);
//}
