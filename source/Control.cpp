#include "Control.h"


using asio::ip::tcp;


Control::Control(Model& model, asio::ip::tcp::socket* socket)
    :   model(model), socket(socket) {
    key_state = SDL_GetKeyboardState(nullptr);
}

void Control::handleInput() {
    SDL_Event Event;
    while (SDL_PollEvent(&Event)) {}

    if (key_state[SDL_SCANCODE_R]) { 
        model.background_color = std::vector<double>{ 1,0,0,1 };
        asio::write(*socket, asio::buffer("i am sending the message R"));
    }
    if (key_state[SDL_SCANCODE_G]) { 
        model.background_color = std::vector<double>{ 0,1,0,1 }; 
        asio::write(*socket, asio::buffer("i am sending the message G"));
    }
    if (key_state[SDL_SCANCODE_B]) { 
        model.background_color = std::vector<double>{ 0,0,1,1 };
        asio::write(*socket, asio::buffer("i am sending the message B"));
    }
}