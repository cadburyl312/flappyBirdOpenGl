#include <iostream>
#include <iomanip>
#include <format>
#include "bird.h"
#include "Model.h"
#include "Control.h"
#include "GameObject.h"
#include <chrono>


#include "SDL2/SDL.h"
#include "GL/glew.h"

#include <OpenGL/gl.h>
#include <array>
#include <iostream>
#include <asio.hpp>
#include "View.h"

#include <thread>
#include <chrono>

void SDL_config();
void init(SDL_Window*& window);
void tearDown(SDL_Window*& window);
void updatePlayerPosition(asio::ip::tcp::socket* socket, GameObject player, int clientId);

using asio::ip::tcp;


int main(int argc, char** argv)
{    
    asio::io_context io_context;
    tcp::resolver resolver(io_context);

    tcp::resolver::results_type endpoints =resolver.resolve("127.0.0.1", "5001");

    tcp::socket socket(io_context);
    asio::connect(socket, endpoints);

    std::array<char, 128> buf;
    std::error_code error;

     asio::steady_timer t(io_context, asio::chrono::seconds(2));
    t.wait();

    size_t len = socket.read_some(asio::buffer(buf), error);

    const std::string prefix = "Your client unique ID is:";

    int clientId = 0;
    std::string msg(buf.data());

    if (msg.rfind(prefix, 0) == 0) {
        std::cout << "Message starts correctly, grabbing client Id\n";
        clientId = stoi(msg.substr(prefix.size()));
        std::cout <<  clientId;

    }



    GameObject player = GameObject();
    player.setObjectType("Player");


    socket.non_blocking(true);

    std::cout.write(buf.data(), len);


    const double timeStep = 10;
    double frameTime = 0.0;
    double lastTime = SDL_GetTicks();
    double currentTime;

    SDL_Window* main_window;
    init(main_window);
    SDL_config();
    
    Model model;
    Control control = Control(model, &socket);

    View view = View(model);
    view.TriangleShader();
    SDL_Event Event;
    //size_t len;
    while (true) {
        len = socket.read_some(asio::buffer(buf), error);
        if (len > 0) {
            std::cout.write(buf.data(), len);
        }
        currentTime = SDL_GetTicks();
        frameTime += currentTime - lastTime;
        lastTime = currentTime;

        

        glClearColor(model.background_color[0], model.background_color[1], model.background_color[2], model.background_color[3]);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glFlush();
        while (frameTime>timeStep) {
            frameTime -= timeStep;
        }

        control.handleInput(frameTime, player);

        while (SDL_PollEvent(&Event)){}
        SDL_GL_SwapWindow(main_window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        updatePlayerPosition(&socket, player, clientId);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    tearDown(main_window);
    return 0;
}

void SDL_config()
{
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
}


void init(SDL_Window*& window) {
    SDL_Init(SDL_INIT_EVERYTHING);


    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);


    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);


    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

    window = SDL_CreateWindow("game", 20, 40, 600,600,SDL_WINDOW_OPENGL);
    if (window == NULL) {
        std::cout << "Failed to create game windows";
    }
    SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1);

    auto glewExperimental = GL_TRUE;
    glewInit();
}

void tearDown(SDL_Window*& window) {
    SDL_GL_DeleteContext(window);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void updatePlayerPosition(asio::ip::tcp::socket* socket, GameObject player, int clientId) {
    std::string playerPositionUpdate = std::to_string(clientId) + ":" + std::to_string(player.getX()) + ":" + std::to_string(player.getX()) + ":" + std::to_string(player.getY()) + ":" + std::to_string(player.getZ());
     asio::write(*socket, asio::buffer(playerPositionUpdate));
}