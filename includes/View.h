#ifndef VIEW
#define VIEW
 
#include "SDL2/SDL.h"
#include "Model.h"
#include "GL/glew.h"
#include <fstream>
#include <string>
#include <iostream>
 
class View {
private:
    GLuint triangle_settings;
    GLuint triangle_buffer;
    GLuint color_buffer;
    GLuint shader_program;
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint element_buffer;
 
    Model& model;   
public:
    View(Model& model);
    void render(SDL_Window* window);
    void TriangleShader();
};
 
 
//
//Utilities
//
GLuint LoadShader(std::string shader_file_name, GLenum shader_type);
void CheckLinkStatus(GLuint& shader_program);
 
#endif