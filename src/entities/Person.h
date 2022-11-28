//
// Created by Edward Gigolaev on 28.11.2022.
//

#ifndef GAME_PERSON_H
#define GAME_PERSON_H

enum moveDirection {
    left,
    right,
    forward,
    back
};

class Person {
public:
    double x = 0;
    double y = 0;
    double fov = 60;
    double headRotation = -90;
private:
    double speed = 20;
    double rotationSpeed = 3;
    static bool canMove(double x, double y);
public:
    ~Person();

    void setCoords(double x, double y);
    void rotate(moveDirection direction);
    void move(moveDirection direction);
};

#endif //GAME_PERSON_H
