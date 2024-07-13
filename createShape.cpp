#define GLM_ENABLE_EXPERIMENTAL
#include "createShape.h"
#define PI 3.14159265358979323846

vector<vec3> getHeartGeometry(float rx, float ry, int precision)
{
	float step = 2 * PI / precision;
	vector<vec3> vertices;
	for (int i = 0; i <= precision + 2; i++)
	{
		float theta_i = (float)i * step;
		float x = rx * 16 * pow(sin(theta_i), 3);
		float y = ry * (13 * cos(theta_i) - 5 * cos(2 * theta_i) - 2 * cos(3 * theta_i) - cos(4 * theta_i));
		vertices.push_back(vec3(x, y, 0.0f));
	}
	return vertices;
}

// crea un triangolo isoscele
vector<vec3> createTriangle(float size)
{
	vector<vec3> vertices;
	vertices.push_back(vec3(0.0f, 0.0f, 0.0f));
	vertices.push_back(vec3(-size / 2, -size, 0.0f));
	vertices.push_back(vec3(size / 2, -size, 0.0f));
	return vertices;
}

// crea un rettangolo
vector<vec3> createRectangle(float w, float h)
{
	float halfWidth = w / 2.0f;
	float halfHeight = h / 2.0f;

	vector<vec3> vertices;
	vertices.push_back(vec3(-halfWidth, -halfHeight, 0.0f)); // Bottom-left
	vertices.push_back(vec3(halfWidth, -halfHeight, 0.0f));  // Bottom-right
	vertices.push_back(vec3(halfWidth, halfHeight, 0.0f));   // Top-right
	vertices.push_back(vec3(-halfWidth, halfHeight, 0.0f));  // Top-left
	vertices.push_back(vec3(-halfWidth, -halfHeight, 0.0f)); // Bottom-left (to close the rectangle)
	return vertices;
}