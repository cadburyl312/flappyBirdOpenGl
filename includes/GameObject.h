#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include <string>
#include <array>

class GameObject {
private:
    float x;
    float y;
    float z;
    std::string objectType;
    std::array<float, 3> velocityVector;

public:

    GameObject();
    GameObject(float x, float y, float z, const std::string& type, const std::array<float, 3>& velocity);


    float getX() const;
    float getY() const;
    float getZ() const;
    std::string getObjectType() const;
    std::array<float, 3> getVelocityVector() const;


    void setX(float newX);
    void setY(float newY);
    void setZ(float newZ);
    void setObjectType(const std::string& newType);
    void setVelocityVector(const std::array<float, 3>& newVelocity);
};

#endif