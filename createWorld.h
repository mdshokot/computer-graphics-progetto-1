#pragma once
#include "geometricShape.h"
#include "entities/Player.h"

// Create a vector of entities that represent the bullets
vector<GeometricShape*> createLives(float numberOfLives, float radius, GLuint MatModel);

Player* createPlayer(GLuint MatModel);