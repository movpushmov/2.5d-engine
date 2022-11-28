#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cmath>
#include <thread>
#include <chrono>
#include "entities/World.h"
#include "render/Ray.h"
#include "utils/math.h"

static float WINDOW_WIDTH = 1800;
static float WINDOW_HEIGHT = 1800;
static float MINIMAP_SCALE = 5;

std::vector<Ray*>* rayCast() {
    std::vector<Ray*>* collisions = new std::vector<Ray*>(0);

    double left = World::person->headRotation - World::person->fov / 2;
    double right = World::person->headRotation + World::person->fov / 2;

    double step = 0.25;

    for (double angle = left; angle < right; angle += step) {
        Ray* ray = new Ray(World::person->x, World::person->y, angle);
        bool hasCollision = false;

        while (!hasCollision) {
            for (auto object : World::gameObjects) {
                if (checkCollision(object, ray->x, ray->y)) {
                    hasCollision = true;
                    collisions->push_back(ray);
                    break;
                }
            }

            if (!hasCollision) {
                ray->x += 0.5 * cos(radians(ray->angel));
                ray->y += 0.5 * sin(radians(ray->angel));
            }
        }
    }

    return collisions;
}

//
// Created by Edward Gigolaev on 28.11.2022.
//
void renderMinimap(std::vector<Ray*>* rays) {
    {
        sf::RectangleShape minimapShade(sf::Vector2f(WINDOW_WIDTH / MINIMAP_SCALE, WINDOW_HEIGHT / MINIMAP_SCALE));
        minimapShade.setFillColor(sf::Color::Black);

        World::window->draw(minimapShade);
    }

    for (auto object : World::gameObjects) {
        sf::RectangleShape rect(sf::Vector2f(object->width / MINIMAP_SCALE, object->height / MINIMAP_SCALE));
        rect.move(sf::Vector2f(object->x / MINIMAP_SCALE, object->y / MINIMAP_SCALE));
        rect.setFillColor(sf::Color::White);

        World::window->draw(rect);
    }

    for (auto ray : *rays) {
        sf::Vertex line[] =
        {
        sf::Vertex(sf::Vector2f(World::person->x / MINIMAP_SCALE, World::person->y / MINIMAP_SCALE), sf::Color(255, 0, 0, 255)),
        sf::Vertex(sf::Vector2f(ray->x / MINIMAP_SCALE, ray->y / MINIMAP_SCALE), sf::Color(255, 0, 0, 255))
        };

        World::window->draw(line, 2, sf::Lines);
    }
}

void render() {
    while (!World::closed) {
        if (!World::window->isOpen()) {
            return;
        }

        World::window->clear();

        if (ControlsPressed::w) {
            World::person->move(forward);
        }

        if (ControlsPressed::s) {
            World::person->move(back);
        }

        if (ControlsPressed::a) {
            World::person->rotate(left);
        }

        if (ControlsPressed::d) {
            World::person->rotate(right);
        }

        auto collisions = rayCast();

        float lastX = 0;
        for (auto collision : *collisions) {
            auto distance = sqrt(
                    pow(abs(World::person->x - collision->x), 2) +
                    pow(abs(World::person->y - collision->y), 2)
            );

            sf::RectangleShape rect(sf::Vector2f(
                    7.468, WINDOW_HEIGHT / 10 + WINDOW_HEIGHT / distance * 60
            ));

            rect.move(lastX, WINDOW_HEIGHT / 2 - WINDOW_HEIGHT / distance * 15);
            lastX += 7.468;

            float alfa = -distance/1000 + 1;

            rect.setFillColor(sf::Color(255, 255, 255, 255 * alfa));

            World::window->draw(rect);
        }

        renderMinimap(collisions);

        for (auto collision : *collisions) {
            delete collision;
        }

        World::window->display();

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(16ms);
    }
}