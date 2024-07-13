#include "Entity.h"

Entity::Entity(GLuint initialModel, float maxSpeed, float maxForce)
    : GeometricShape(initialModel), maxSpeed(maxSpeed), maxForce(maxForce){}

void Entity::setVelocity(vec3 newVelocity) {
    velocity = newVelocity;
}

vec3 Entity::getVelocity() {
    return velocity;
}

void Entity::setAcceleration(vec3 newAcceleration) {
    acceleration = newAcceleration;
}

vec3 Entity::getAcceleration() {
    return acceleration;
}

float Entity::getMaxSpeed() {
    return maxSpeed;
}

float Entity::getMaxForce() {
    return maxForce;
}

bool Entity::checkCollision(const glm::vec3& pos1, float radius1, const glm::vec3& pos2, float radius2) {
    float distance = glm::length(pos1 - pos2);
    float combinedRadii = radius1 + radius2;
    return distance <= combinedRadii;
}