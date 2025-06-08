#include <iostream>
#include <iomanip>
#include <format>
#include "bird.h"
#include <GL/glew.h>
#include <GL/freeglut.h>

void display();
void ResizeFunction(int width, int height);

int main(int argc, char** argv)
{
    const char* bird1 = "first Bird";
    std::cout << "Hello World!\n";

    Bird firstBird(5, 5, 5, bird1);
    std::cout << std::fixed << std::setprecision(2)
              << firstBird.getBirdX() << '\n'
              << firstBird.getBirdY() << '\n'
              << firstBird.getBirdZ() << '\n';

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
    fprintf(
        stdout,
        "INFO: OpenGL Version: %s\n",
        glGetString(GL_VERSION)
    );

    glutMainLoop();
    return 0;
}

void display() {
    // Clear the color buffer to the color set by glClearColor
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void ResizeFunction(int Width, int Height)
{
  glViewport(0, 0, Width, Height);
}
