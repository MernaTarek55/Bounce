#pragma once
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>
#include "box2d/box2d.h"

using namespace std;
using namespace sf;


// Struct for storing grid positions
struct Position {
    int row;
    int col;
};

extern char grid[15][48];
const float SCALE = 30.0f; // Box2D scale factor: 1 meter = 30 pixels
const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;
const int SCENE_WIDTH = 15;  // Number of grid cells wide per scene
const int SCENE_HEIGHT = 15; // Number of grid cells tall per scene
const int player_Scene_WIDTH = 5;
const int player_Scene_HEIGHT = 5;

