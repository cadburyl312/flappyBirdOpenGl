#include <iostream>
#include <iomanip>
#include <format>
#include "bird.h"
#include "Model.h"
#include "Control.h"
#include <chrono>

#include "SDL2/SDL.h"
#include "GL/glew.h"

#include <OpenGL/gl.h>
#include <array>
#include <iostream>
#include <asio.hpp>

void SDL_config();
void init(SDL_Window*& window);
void tearDown(SDL_Window*& window);

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

    socket.non_blocking(true);

    std::cout.write(buf.data(), len);


    const double timeStep = 10;
    double frameTime = 0.0;
    double lastTime = SDL_GetTicks();
    double currentTime;
    const char* bird1 = "first Bird";
    std::cout << "Hello World!\n";

    Bird firstBird(5, 5, 5, bird1);
    std::cout << std::fixed << std::setprecision(2)
              << firstBird.getBirdX() << '\n'
              << firstBird.getBirdY() << '\n'
              << firstBird.getBirdZ() << '\n';

    SDL_Window* main_window;
    init(main_window);
    SDL_config();
    
    Model model;
    Control control = Control(model, &socket);
    SDL_Event Event;
    size_t len;
    while (true) {
        len = socket.read_some(asio::buffer(buf), error);
        if (len > 0) {
            std::cout.write(buf.data(), len);
        }
        currentTime = SDL_GetTicks();
        frameTime += currentTime - lastTime;
        lastTime = currentTime;

        control.handleInput();

        glClearColor(model.background_color[0], model.background_color[1], model.background_color[2], model.background_color[3]);
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
        while (frameTime>timeStep) {
            frameTime -= timeStep;
        }
        while (SDL_PollEvent(&Event)){}
        SDL_GL_SwapWindow(main_window);
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

    window = SDL_CreateWindow("bird game", 20, 40, 600,600,SDL_WINDOW_OPENGL);
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