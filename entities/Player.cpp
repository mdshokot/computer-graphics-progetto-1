#pragma once
#include "Player.h"
#include "../createShape.h"
#include <cmath>
#include <iostream>

Player::Player(GLuint initialModel, float maxSpeed, float playerAcceleration, float deceleration, float rotationSpeed)
    : Entity(initialModel, maxSpeed, playerAcceleration), // Initialize Entity with maxSpeed and playerAcceleration
    deceleration(deceleration),
    rotationSpeed(rotationSpeed),
    playerAngle(0.0f),
    targetAngle(0.0f),
    playerAcceleration(playerAcceleration) { // Initialize playerAcceleration
}

void Player::update(float deltaTime) {
    // Interpolate the current angle towards the target angle
    float angleDifference = targetAngle - playerAngle;
    if (angleDifference > 180.0f) angleDifference -= 360.0f;
    if (angleDifference < -180.0f) angleDifference += 360.0f;
    playerAngle += angleDifference * rotationSpeed * deltaTime;

    setAngle(playerAngle);

    glm::vec3 currentVelocity = getVelocity();
    if (glm::length(currentVelocity) != 0.0f) {
        // Calculate the movement vector based on the player's angle
        float angleRad = glm::radians(playerAngle);
        glm::vec3 direction = glm::vec3(-sin(angleRad), cos(angleRad), 0.0f);

        updatePos(direction * glm::length(currentVelocity));

        // Apply deceleration
        currentVelocity -= glm::normalize(currentVelocity) * deceleration;
        if (glm::length(currentVelocity) < 0.0f)
            currentVelocity = glm::vec3(0.0f);

        setVelocity(currentVelocity);
    }
}


void Player::rotateTowards(float angle) {
    targetAngle = angle;
}

float Player::getPlayerAngle() const {
    return playerAngle;
}

void Player::setPlayerAngle(float angle) {
    playerAngle = angle;
}

float Player::getTargetAngle() const {
    return targetAngle;
}

void Player::setTargetAngle(float angle) {
    targetAngle = angle;
}

float Player::getPlayerAcceleration() const {
    return playerAcceleration;
}

int Player::getPoints() {
    return points;
}
void Player::updatePoints() {
    points += 10;
}


