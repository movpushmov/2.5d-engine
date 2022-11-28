#include "SFML/Graphics.hpp"
#include "src/entities/GameObject.h"
#include "src/entities/World.h"
#include "src/render.h"
#include <vector>
#include <thread>

std::vector<GameObject*> getObjects(std::vector<std::vector<int>> map, double width, double height) {
    double fieldWidth = width / (double)(map.size() + 2);
    double fieldHeight = height / (double)(map.size() + 2);

    std::vector<GameObject*> objects = {};
    int lastWidth;

    for (int i = 0; i < map.size(); i++) {
        lastWidth = 0;
        int lastStartX = -1;

        for (int j = 0; j < map.size(); j++) {
            if (map[i][j] == 1) {
                lastWidth++;

                if (lastStartX == -1) {
                    lastStartX = j;
                }
            }

            if (map[i][j] == 0 || j == map.size() - 1) {
                if (lastWidth != 0) {
                    objects.push_back(new GameObject(
                            lastStartX * fieldWidth + fieldWidth,
                            i * fieldHeight + fieldHeight,
                            lastWidth * fieldWidth,
                            fieldHeight
                    ));
                    lastWidth = 0;
                    lastStartX = -1;
                }
            }
        }
    }

    return objects;
}

static float WINDOW_WIDTH = 1800;
static float WINDOW_HEIGHT = 1800;
static float WALL_WEIGHT = 25;

int main()
{
    std::vector<std::vector<int>> map = {
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 1, 1, 1, 0, 0, 0, 0, 0 },
            { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 1, 0, 1, 0, 0, 0, 0, 0 },
            { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    };

    World::gameObjects = getObjects(map, WINDOW_WIDTH, WINDOW_HEIGHT);
    World::person = new Person();

    World::gameObjects.push_back(new GameObject(0, 0, WINDOW_WIDTH, WALL_WEIGHT));
    World::gameObjects.push_back(new GameObject(0, 0, WALL_WEIGHT, WINDOW_HEIGHT));
    World::gameObjects.push_back(new GameObject(WINDOW_WIDTH - WALL_WEIGHT, 0, WALL_WEIGHT, WINDOW_HEIGHT));
    World::gameObjects.push_back(new GameObject(0, WINDOW_HEIGHT - WALL_WEIGHT, WINDOW_WIDTH, WALL_WEIGHT));

    World::person->setCoords(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game");
    World::window = &window;

    std::thread thread(render);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                World::closed = true;
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Key::W) {
                    ControlsPressed::w = true;
                }

                if (event.key.code == sf::Keyboard::Key::A) {
                    ControlsPressed::a = true;
                }

                if (event.key.code == sf::Keyboard::Key::S) {
                    ControlsPressed::s = true;
                }

                if (event.key.code == sf::Keyboard::Key::D) {
                    ControlsPressed::d = true;
                }
            }

            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Key::W) {
                    ControlsPressed::w = false;
                }

                if (event.key.code == sf::Keyboard::Key::A) {
                    ControlsPressed::a = false;
                }

                if (event.key.code == sf::Keyboard::Key::S) {
                    ControlsPressed::s = false;
                }

                if (event.key.code == sf::Keyboard::Key::D) {
                    ControlsPressed::d = false;
                }
            }
        }
    }

    return 0;
}
