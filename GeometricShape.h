#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
using namespace glm;
using namespace std;

class GeometricShape
{
private:
    vector<vec3> vertices; // Array for vertex positions
    vector<vec4> colors;   // Array for vertex colors
    GLuint vaoID;          // Vertex Array Object ID
    GLuint vboID_v;        // Vertex Buffer Object ID for positions
    GLuint vboID_c;        // Vertex Buffer Object ID for colors
    GLuint MatModel;
    mat4 model = mat4(1.0f);            // Model of the object
    vec3 size = vec3(1.0f, 1.0f, 1.0f);
    vec3 pos = vec3(0.0f, 0.0f, 0.0f);
    float angle = 0.0f;
    float radius;

public:
    GeometricShape(GLuint initialModel);
    void createPolygonalShape(vector<vec3> polygonVertices, vec4 color1, vec4 color2);
    void initVao();
    vec3 getPosition();
    void updatePos(vec3 newPos);
    void updateScale(vec3 newScale);
    void setAngle(float newAnglse);
    float getAngle();
    mat4 getModel();
    void draw();
    float getRadius();
    void setRadius(float newRadius);
    GLuint getMatModel();
};