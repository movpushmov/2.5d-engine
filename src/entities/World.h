//
// Created by Edward Gigolaev on 28.11.2022.
//

#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include "GameObject.h"
#include "Person.h"

class ControlsPressed {
public:
    static bool w;
    static bool a;
    static bool s;
    static bool d;
};

class World {
public:
    static std::vector<GameObject*> gameObjects;
    static Person* person;
    static sf::RenderWindow* window;
    static bool closed;
};


#endif //GAME_WORLD_H
