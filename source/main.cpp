#include <iostream>
#include <iomanip>
#include <format>
#include "bird.h"
#include <GL/freeglut.h>
#include <GL/gl.h>

void display();

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
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("My First FreeGLUT Window");

    // Set your clear color here (e.g. teal)
    glClearColor(0.0f, 0.5f, 0.5f, 1.0f);

    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

void display() {
    // Clear the color buffer to the color set by glClearColor
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}
