#pragma once
#include "createWorld.h"
#include "createShape.h"
#include "globals.h"
#include <iostream>

vector<GeometricShape*> createLives(float numberOfLives, float radius, GLuint MatModel)
{
    vec4 red = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    vec4 pink = vec4(0.5f, 0.2f, 0.2f, 1.0f);
    vector<GeometricShape*> lives;

    // Create GeometricShape objects for each life
    for (int i = 0; i < numberOfLives; i++) {
        lives.push_back(new GeometricShape(MatModel));
    }

    // Calculate initial positions for hearts
    float startX = radius; // Starting x position from left edge
    float startY = height - radius - 10; // Starting y position from top edge
    float xPos = 10.0f;
    // Position hearts one after another in the top-left corner
    for (int i = 0; i < numberOfLives; i++) {
        // Calculate the position for the current heart
        vec3 position = vec3(xPos, startY, 0.0f);

        // Create heart shape and update its position
        lives[i]->createPolygonalShape(getHeartGeometry(radius, radius, 100), red, pink);
        lives[i]->updatePos(position);
        xPos = 10 + (2 * radius * (i+1)) + (i+1) * 20;
    }

    return lives;
}

Player* createPlayer(GLuint MatModel) {

    vec4 color1 = vec4(0.0f, 1.0f, 0.0f, 1.0f); //  verde
    vec4 color2 = vec4(0.0f, 0.0f, 1.0f, 1.0f); //  blu
    Player* player = new Player(MatModel);
    player->createPolygonalShape(createTriangle(30), color1, color2);
    player->updatePos(vec3(width / 2, height / 2, 0));

    return player;
}