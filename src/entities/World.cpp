//
// Created by Edward Gigolaev on 28.11.2022.
//

#include "World.h"

Person* World::person;
sf::RenderWindow* World::window;
std::vector<GameObject*> World::gameObjects = {};
bool World::closed = false;

bool ControlsPressed::w = false;
bool ControlsPressed::a = false;
bool ControlsPressed::s = false;
bool ControlsPressed::d = false;