cmake_minimum_required(VERSION 3.22)
project(gl_start)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH /home/headass/CMake_Modules/)

find_package(SDL2 REQUIRED)
find_package(GLFW REQUIRED)
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

find_package(SDL2TTF REQUIRED)

include_directories(include)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${SDL2TTF_INCLUDE_DIRS})

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
    "src/*.cpp"
)


add_executable(gl_start ${SRC})

target_link_libraries(gl_start SDL2 GLFW OpenGL  GLEW SDL2_ttf ${SDL2_LIBRARIES})