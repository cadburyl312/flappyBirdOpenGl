#ifndef CONTROL
#define CONTROL
 
#include "SDL2/SDL.h"
#include "Model.h"
#include <array>
#include <iostream>
#include <asio.hpp>
 
class Control {
private:
    Model& model;
    asio::ip::tcp::socket* socket; 
    const Uint8 *key_state;
public:
    void handleInput(double frameTime, GameObject player);
    Control(Model& model, asio::ip::tcp::socket* socket);
};
 
#endif