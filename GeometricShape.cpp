
#include "GeometricShape.h"

#include <iostream>


// Constructor definition
GeometricShape::GeometricShape(GLuint initialModel) {
    MatModel = initialModel;
}

void GeometricShape::createPolygonalShape(vector<vec3> polygonVertices, vec4 color1, vec4 color2) {
    vertices.push_back(vec3(0.0f, 0.0f, 0.0f));
    colors.push_back(color2);
    for (vec3 vertex : polygonVertices) {
        vertices.push_back(vec3(vertex.x, vertex.y, 0.0f));
        colors.push_back(color1);
    }
}

void GeometricShape::initVao() {
    // Generate and bind the Vertex Array Object
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
    // Generate and bind the Vertex Buffer Object for positions
    glGenBuffers(1, &vboID_v);
    glBindBuffer(GL_ARRAY_BUFFER, vboID_v);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec3), vertices.data(), GL_DYNAMIC_DRAW);

    // Define the layout of the vertex data
    glEnableVertexAttribArray(0); // Attribute 0 for positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // Generate and bind the Vertex Buffer Object for colors
    glGenBuffers(1, &vboID_c);
    glBindBuffer(GL_ARRAY_BUFFER, vboID_c);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(vec4), colors.data(), GL_DYNAMIC_DRAW);

    // Define the layout of the color data
    glEnableVertexAttribArray(1); // Attribute 1 for colors
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // Unbind the VAO to prevent accidental modification
    glBindVertexArray(0);
}
vec3 GeometricShape::getPosition() {
    return pos;
}

void GeometricShape::updatePos(vec3 newPos) {
    pos += newPos;
    // Create a translation matrix based on the updated position and update the model matrix
    model = translate(mat4(1.0f), pos) * rotate(mat4(1.0f), radians(angle), vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), size);
}

void GeometricShape::updateScale(vec3 newScale) {
    size += newScale;
    // Create a scaling matrix based on the updated size and update the model matrix
    model = translate(mat4(1.0f), pos) * rotate(mat4(1.0f), radians(angle), vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), size);
}

void GeometricShape::setAngle(float newAngle) {
    angle = newAngle;
    // Update the model matrix with the new angle
    model = translate(mat4(1.0f), pos) * rotate(mat4(1.0f), radians(angle), vec3(0.0f, 0.0f, 1.0f)) * scale(mat4(1.0f), size);
}

float GeometricShape::getAngle() {
    return angle;
}

float GeometricShape::getRadius() {
    return radius;
}

void GeometricShape::setRadius(float newRadius) {
    radius = newRadius;
}

mat4 GeometricShape::getModel() {
    return model;
}

GLuint GeometricShape::getMatModel() {
    return MatModel;
}

void GeometricShape::draw() {
    // Bind the VAO
    glBindVertexArray(vaoID);
    // Draw the shape

    glUniformMatrix4fv(MatModel, 1, GL_FALSE, value_ptr(model));
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size() + 2);
    // Unbind the VAO after drawing
    glBindVertexArray(0);
}
