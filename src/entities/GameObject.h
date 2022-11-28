//
// Created by Edward Gigolaev on 28.11.2022.
//

#ifndef GAME_GAMEOBJECT_H
#define GAME_GAMEOBJECT_H


class GameObject {
public:
    double x;
    double y;
    double width;
    double height;

    GameObject(double x, double y, double width, double height);
};


#endif //GAME_GAMEOBJECT_H
