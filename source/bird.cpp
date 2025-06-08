#include "bird.h"

Bird::Bird(float x, float y, float z, const char* id) {
    birdX = x;
    birdY = y;
    birdZ = z;
    birdId = id;
}

float Bird::getBirdX() { return birdX; }
float Bird::getBirdY() { return birdY; }
float Bird::getBirdZ() { return birdZ; }
const char* Bird::getBirdId() { return birdId; }