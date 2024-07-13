#pragma once
#include "GeometricShape.h"


class Entity : public GeometricShape {
	private:
		vec3 velocity = vec3(0.0f);
		vec3 acceleration = vec3(0.0f);
		float maxSpeed;
		float maxForce;
		
    public:
		Entity(GLuint initialModel,float maxSpeed = 12.0f, float maxForce = 1.0f);
		static bool checkCollision(const glm::vec3& pos1, float radius1, const glm::vec3& pos2, float radius2);
		void setVelocity(vec3 newVelocity);
		vec3 getVelocity();
		void setAcceleration(vec3 newAcceleration);
		vec3 getAcceleration();
		float getMaxSpeed();
		float getMaxForce();
		
};