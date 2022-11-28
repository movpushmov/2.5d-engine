//
// Created by Edward Gigolaev on 28.11.2022.
//

#ifndef GAME_MATH_H
#define GAME_MATH_H

#include "../entities/GameObject.h"

double radians(double degrees);
bool checkCollision(GameObject* object, double x, double y);

#endif //GAME_MATH_H
