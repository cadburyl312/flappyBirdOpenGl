cmake_minimum_required(VERSION 3.15)

project(MyApp VERSION 1.0 LANGUAGES CXX)

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include the 'includes' directory for header files
include_directories(${CMAKE_SOURCE_DIR}/includes)
include_directories(/opt/homebrew/include)

# Add source files
add_executable(my_app
    source/main.cpp
    source/bird.cpp
    source/Model.cpp
    source/Control.cpp
    source/View.cpp
    source/GameObject.cpp
)

# macOS: Link against the OpenGL framework explicitly


if (APPLE)
    # GLEW
    include_directories(/opt/homebrew/Cellar/glew/2.2.0_1/include)
    link_directories("/opt/homebrew/Cellar/glew/2.2.0_1/lib")
    # SDL2
    include_directories(/opt/homebrew/Cellar/sdl2/2.32.8/include)
    link_directories("/opt/homebrew/Cellar/sdl2/2.32.8/lib")

    target_link_libraries(my_app
        "-framework OpenGL"
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
        /opt/homebrew/Cellar/sdl2/2.32.8/lib/libSDL2.dylib
        /opt/homebrew/Cellar/glew/2.2.0_1/lib/libGLEW.dylib
        pthread
    )
endif()