cmake_minimum_required(VERSION 3.15)

project(MyApp VERSION 1.0 LANGUAGES CXX)

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include the 'includes' directory for header files
include_directories(${CMAKE_SOURCE_DIR}/includes)
include_directories("C:/msys64/mingw64/include")

# Add source files
add_executable(my_app
    source/main.cpp
    source/bird.cpp
)

target_link_libraries(my_app PRIVATE "libfreeglut.dll"
                                      "glew32.dll"
                                      "opengl32.dll"
                                      
)