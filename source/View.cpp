#include "View.h"

View::View(Model& model) :model(model) {

    std::cout << "shaders are loaded in !" << std::endl;

    GLuint vertex_shader = LoadShader(std::string("../source/Shaders/vertex_shader.txt"), GL_VERTEX_SHADER);
    
    std::cout << "Vertex shader ID: " << vertex_shader << std::endl;
    GLuint fragment_shader = LoadShader(std::string("../source/Shaders/fragment_shader.txt"), GL_FRAGMENT_SHADER);
    std::cout << "Fragment shader ID: " << fragment_shader << std::endl;
 
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    std::cout << "Shader program ID: " << shader_program << std::endl;

    std::cout << "shaders are loaded in 222!" << std::endl;
 
    glAttachShader(shader_program, fragment_shader);

    std::cout << "are you a segfault" << std::endl;


    glBindFragDataLocation(shader_program, 0, "color_out");
    

    std::cout << "shaders are loaded in !" << std::endl;
 
    glLinkProgram(shader_program);
    CheckLinkStatus(shader_program);

    std::cout << "shaders are loaded in !" << std::endl;
 
    glDetachShader(shader_program, vertex_shader);
    glDetachShader(shader_program, fragment_shader);

    std::cout << "shaders are loaded in !" << std::endl;
 
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    std::cout << "shaders are loaded in !" << std::endl;
 
    glUseProgram(shader_program);

    std::cout << "shaders are loaded in !" << std::endl;

    glGenVertexArrays(1, &triangle_settings);
    glBindVertexArray(triangle_settings);

    std::cout << "shaders are loaded in !" << std::endl;
 
    float triangle_data[] = {
        -0.5, -0.5, 0, 1.0, 0, 0,
        0.5, -0.5, 0, 1.0, 0, 0,
        0.5,  0.5, 0, 1.0, 0, 0
    };


    std::cout << "shaders are loaded in !" << std::endl;


    glGenBuffers(1, &triangle_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, triangle_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_data), triangle_data, GL_STATIC_DRAW);

    std::cout << "shaders are loaded in !" << std::endl;

    GLint vertex_position_attribute = glGetAttribLocation(shader_program, "vertex_position");
    glVertexAttribPointer(vertex_position_attribute, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),  (void*)0);
    glEnableVertexAttribArray(vertex_position_attribute);

    std::cout << "shaders are loaded in !" << std::endl;
 

    GLint color_in_attribute = glGetAttribLocation(shader_program, "color_input");
    glVertexAttribPointer(color_in_attribute, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(color_in_attribute);

    std::cout << "shaders are loaded in !" << std::endl;
}


GLuint LoadShader(std::string shader_file_name, GLenum shader_type) {
    std::ifstream my_stream(shader_file_name);
    std::string contents = std::string((std::istreambuf_iterator<char>(my_stream)), std::istreambuf_iterator<char>());

    std::cout << "shaders contents";
    std::cout << contents;
    const GLchar* shader_code = contents.c_str();
 
    GLuint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_code, nullptr);
    glCompileShader(shader);
 
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        std::cout << "shader compile error in: " << shader_file_name << std::endl;
        char buffer[512];
        glGetShaderInfoLog(shader, 512, nullptr, buffer);
        std::cout << buffer << std::endl;
    }
    return shader;
}

void CheckLinkStatus(GLuint& shader_program) {
    GLint link_status;
    glGetProgramiv(shader_program, GL_LINK_STATUS, &link_status);
    if (link_status != GL_TRUE) {
        std::cout << "shader linker error in View constructor" << std::endl;
        char buffer[512];
        glGetProgramInfoLog(shader_program, 512, nullptr, buffer);
    }


    //TODO, MODIFY CODE TO MOVE TRIANGLE LOADING INTO SEPERATE FUNCTION VALLED WITHIN VIEW.
}