#pragma once
#include "Entity.h"

class Missile : public Entity {
private:

public:
	Missile(GLuint initialModel, float maxSpeed = 12.0f, float maxForce = 1.0f);
	void seek(vec3 target);
};