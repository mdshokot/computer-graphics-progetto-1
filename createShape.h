#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
using namespace glm;
using namespace std;


vector<vec3> getHeartGeometry(float rx, float ry, int precision);

vector<vec3> createTriangle(float size);

vector<vec3> createRectangle(float width, float height);