#pragma once
#ifndef BIRD_H
#define BIRD_H

class Bird {
private:
    float birdX;
    float birdY;
    float birdZ;
    const char* birdId;

public:
    Bird(float birdX, float birdY, float birdZ, const char* message);

    float getBirdX();
    float getBirdY();
    float getBirdZ();
    const char* getBirdId();
};

#endif
