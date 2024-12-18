#pragma once

#ifndef CIRCLE_H
#define CIRCLE_H

#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <SDL.h>
#undef main // SDL defines main, so we need to undefine it

class Circle {
public:
    // Constructor and Destructor
    Circle(float x, float y, float radius, SDL_Texture* texture, SDL_Renderer* renderer);
    ~Circle();

    // Functions to draw and manipulate the circle
    void draw();
    void move(float x, float y);
    void setPos(float x, float y);
    void setRadius(float radius);
    void setColor(SDL_Color color); // This will now only update the color but not recreate the texture
    void setVelocity(float x, float y);
    void setVelocity(glm::vec2 velocity);
    void setAcceleration(float x, float y);
    void setAcceleration(glm::vec2 acceleration);
    void update(float dt);

    // Getter functions
    glm::vec2 getPos() const;
    float getRadius() const;
    SDL_Color getColor() const;
    glm::vec2 getVelocity() const;
    glm::vec2 getAcceleration() const;

private:
    glm::vec2 pos;           // Position of the circle
    float radius;            // Radius of the circle
    SDL_Color color;         // Color of the circle
    glm::vec2 velocity;      // Velocity of the circle
    glm::vec2 acceleration;  // Acceleration of the circle
    SDL_Texture* circleTexture; // Texture for circle (pre-generated)
    SDL_Renderer* renderer;    // Renderer to use for texture
};

#endif // CIRCLE_H
