#include "GameObject.h"


GameObject::GameObject()
    : x(0.0f), y(0.0f), z(0.0f), objectType("Undefined"), velocityVector({0.0f, 0.0f, 0.0f}) {}


GameObject::GameObject(float x, float y, float z, const std::string& type, const std::array<float, 3>& velocity)
    : x(x), y(y), z(z), objectType(type), velocityVector(velocity) {}


float GameObject::getX() const { return x; }
float GameObject::getY() const { return y; }
float GameObject::getZ() const { return z; }
std::string GameObject::getObjectType() const { return objectType; }
std::array<float, 3> GameObject::getVelocityVector() const { return velocityVector; }


void GameObject::setX(float newX) { x = newX; }
void GameObject::setY(float newY) { y = newY; }
void GameObject::setZ(float newZ) { z = newZ; }
void GameObject::setObjectType(const std::string& newType) { objectType = newType; }
void GameObject::setVelocityVector(const std::array<float, 3>& newVelocity) { velocityVector = newVelocity; }