//
// Created by Edward Gigolaev on 28.11.2022.
//

#include "Person.h"
#include "../utils/math.h"
#include "World.h"

#include <cmath>

Person::~Person() = default;

void Person::setCoords(double x, double y) {
    this->x = x;
    this->y = y;
}

void Person::rotate(moveDirection direction) {
    if (direction == left) {
        this->headRotation -= this->rotationSpeed;
    } else if (direction == right) {
        this->headRotation += this->rotationSpeed;
    }
}

void Person::move(moveDirection direction) {
    double newX = this->x;
    double newY = this->y;

    if (direction == forward) {
        newX += this->speed * cos(radians(this->headRotation));
        newY += this->speed * sin(radians(this->headRotation));
    } else if (direction == back) {
        newX += this->speed * cos(radians(this->headRotation + 180));
        newY += this->speed * sin(radians(this->headRotation + 180));
    }

    if (Person::canMove(newX, newY)) {
        this->x = newX;
        this->y = newY;
    }
}

bool Person::canMove(double x, double y) {
    for (auto object : World::gameObjects) {
        if (checkCollision(object, x, y)) {
            return false;
        }
    }

    return true;
}