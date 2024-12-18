#include <circle.h>

// Constructor: Initialize position, radius, color, and use pre-generated texture
Circle::Circle(float x, float y, float radius, SDL_Texture* texture, SDL_Renderer* renderer)
    : pos(x, y), radius(radius), color({ 0, 0, 0, 255 }), velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f), renderer(renderer), circleTexture(texture) {
    // No need to create the texture here, just use the one passed in the constructor
}

// Destructor: Clean up the texture when done
Circle::~Circle() {
    // No need to destroy the texture here, it's managed outside this class
    // (handled in main when cleaning up textures)
}

// Draw the circle using the pre-created texture
void Circle::draw() {
    if (!circleTexture) {
        std::cerr << "Error: Circle texture is not initialized!" << std::endl;
        return; // Early exit if texture is not initialized
    }

    // Define destination rectangle for positioning and scaling the circle texture
    SDL_Rect dstRect = { (int)(pos.x - radius), (int)(pos.y - radius), (int)(2 * radius), (int)(2 * radius) };

    // Draw the circle texture at the specified position and scale
    SDL_RenderCopyEx(renderer, circleTexture, NULL, &dstRect, 0.0, NULL, SDL_FLIP_NONE);
}

// Move the circle by a certain amount (used for position updates)
void Circle::move(float x, float y) {
    pos.x += x;
    pos.y += y;
}

// Set the position of the circle directly
void Circle::setPos(float x, float y) {
    pos.x = x;
    pos.y = y;
}

// Set the radius of the circle
void Circle::setRadius(float radius) {
    this->radius = radius;
    // No need to recreate the texture, as we are reusing pre-generated textures
}

// Set the color of the circle
void Circle::setColor(SDL_Color color) {
    this->color = color;
    // Colors are applied to the pre-generated textures, so no need to recreate the texture
}

// Set the velocity of the circle using individual components
void Circle::setVelocity(float x, float y) {
    velocity = glm::vec2(x, y);
}

// Set the velocity of the circle using a glm::vec2
void Circle::setVelocity(glm::vec2 velocity) {
    this->velocity = velocity;
}

// Set the acceleration of the circle using individual components
void Circle::setAcceleration(float x, float y) {
    acceleration = glm::vec2(x, y);
}

// Set the acceleration of the circle using a glm::vec2
void Circle::setAcceleration(glm::vec2 acceleration) {
    this->acceleration = acceleration;
}

// Update the position of the circle based on velocity and acceleration
void Circle::update(float dt) {
    // Update velocity based on acceleration
    velocity += acceleration * dt;

    // Update position based on velocity
    pos += velocity * dt;
}

// Getter functions
glm::vec2 Circle::getPos() const {
    return pos;
}

float Circle::getRadius() const {
    return radius;
}

SDL_Color Circle::getColor() const {
    return color;
}

glm::vec2 Circle::getVelocity() const {
    return velocity;
}

glm::vec2 Circle::getAcceleration() const {
    return acceleration;
}
