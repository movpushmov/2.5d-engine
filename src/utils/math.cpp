//
// Created by Edward Gigolaev on 28.11.2022.
//
#include <cmath>
#include "../entities/GameObject.h"

double radians(double degrees) {
    return degrees * M_PI / 180;
}

bool checkCollision(GameObject* object, double x, double y) {
    return (
        object->x <= x && object->x + object->width >= x &&
        object->y <= y && object->y + object->height >= y
    );
}