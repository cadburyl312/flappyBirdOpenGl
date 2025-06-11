#include <iostream>
#include <iomanip>
#include <format>
#include "bird.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <chrono>


void display();
void ResizeFunction(int width, int height);
void initWindow(int argc, char** argv);

unsigned FrameCount = 0;

static auto last = std::chrono::high_resolution_clock::now();


int main(int argc, char** argv)
{
    const char* bird1 = "first Bird";
    std::cout << "Hello World!\n";

    Bird firstBird(5, 5, 5, bird1);
    std::cout << std::fixed << std::setprecision(2)
              << firstBird.getBirdX() << '\n'
              << firstBird.getBirdY() << '\n'
              << firstBird.getBirdZ() << '\n';

    initWindow(argc, argv);

    GLenum glew = glewInit();

    if (GLEW_OK != glew) {
        fprintf(
        stderr,
        "ERROR: %s\n",
        glewGetErrorString(glew)
        );
        exit(EXIT_FAILURE);
    }

    fprintf(
        stdout,
        "INFO: OpenGL Version: %s\n",
        glGetString(GL_VERSION)
    );
    glutMainLoop();

    return 0;
}

void display() {

    glClear(GL_COLOR_BUFFER_BIT);

    glFlush();
     auto now = std::chrono::high_resolution_clock::now();
     auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last).count();
     if (elapsed >= 1000) {
        double fps = FrameCount * 1000.0 / elapsed;
                std::cout << std::fixed << std::setprecision(2)
                  << "fps is " << fps << '\n';

        FrameCount = 0;
        last = now;
     }
     FrameCount ++;
}

void ResizeFunction(int Width, int Height)
{
  glViewport(0, 0, Width, Height);
}

void initWindow(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitContextVersion(4, 0);

    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("My First FreeGLUT Window");

    // Set your clear color here (e.g. teal)
    glClearColor(0.0f, 0.5f, 0.5f, 1.0f);

    glutReshapeFunc(ResizeFunction);
    glutDisplayFunc(display);
}