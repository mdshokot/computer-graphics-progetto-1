#pragma once
#include "../Entity.h"



class Projectile : public Entity {
private:

public:
	Projectile(GLuint initialModel, const glm::vec3& position, const glm::vec3& velocity);
	void update(float deltaTime);
	bool isOutOfBounds(float worldWidth, float worldHeight);
	bool checkCollisionWithMissile(const glm::vec3& missilePosition, float missileRadius);
};