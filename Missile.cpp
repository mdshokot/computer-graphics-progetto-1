#pragma once
#include "Missile.h"
#include <cmath>
#define PI 3.14159265358979323846

Missile::Missile(GLuint initialModel, float maxSpeed, float maxForce)
    : Entity(initialModel,maxSpeed, maxForce) {
    
}


void Missile::seek(vec3 target) {
    // Calculate desired velocity
    vec3 desired = glm::normalize(target - getPosition()) * getMaxSpeed();

    // Calculate steering force
    vec3 steer = desired - getVelocity();
    steer = glm::clamp(steer, -getMaxForce(), getMaxForce());

    // Apply acceleration
    setAcceleration(steer);

    // Update velocity
    vec3 newVelocity = getVelocity() + getAcceleration();
    newVelocity = glm::clamp(newVelocity, -getMaxSpeed(), getMaxSpeed());
    setVelocity(newVelocity);

    // Update position
    updatePos(getVelocity());
    // Calculate angle to face the direction of velocity
    if (glm::length(getVelocity()) > 0.0001f) { // Ensure velocity is not zero
        setAngle(atan2(-getVelocity().x, getVelocity().y) * 180.0f / PI);
    }
}