#pragma once
#include "Projectile.h"


Projectile::Projectile(GLuint initialModel, const glm::vec3& position, const glm::vec3& velocity)
    : Entity(initialModel) { 
    updatePos(position);
    setVelocity(velocity);
}
void Projectile::update(float deltaTime) {
        // Update position based on velocity
        glm::vec3 currentPosition = getPosition();
        updatePos(getVelocity());
}


bool Projectile::isOutOfBounds(float worldWidth, float worldHeight) {
    // Check if projectile is out of bounds of the world
    glm::vec3 position = getPosition();
    if (position.x < 0.0f || position.x > worldWidth || position.y < 0.0f || position.y > worldHeight) {
        return true;
    }
    return false;
}

bool Projectile::checkCollisionWithMissile(const glm::vec3& missilePosition, float missileRadius) {
    glm::vec3 projectilePosition = getPosition();
    float distance = glm::length(projectilePosition - missilePosition);
    if (distance < (getRadius() + missileRadius)) {
        return true; 
    }
    return false;
}