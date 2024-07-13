#pragma once
#include "../Entity.h"

class Player : public Entity {
private:
    float deceleration;
    float rotationSpeed;
    float playerAngle;
    float targetAngle;
    float playerAcceleration; 
    int points = 0;

public:
    Player(GLuint initialModel, float maxSpeed = 11.0f, float playerAcceleration = 1.7f, float deceleration = 0.5f, float rotationSpeed = 6.0f);

    void update(float deltaTime);
    void rotateTowards(float angle);
    float getPlayerAngle() const;
    void setPlayerAngle(float angle);
    float getTargetAngle() const;
    void setTargetAngle(float angle);
    float getPlayerAcceleration() const; 
    int getPoints();
    void updatePoints();
};