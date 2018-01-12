cmake_minimum_required(VERSION 3.10)
project(grafikaGL)

set(CMAKE_CXX_STANDARD 14)

add_executable(grafikaGL main.cpp ex1.cpp ex2.cpp ex3.cpp)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

target_link_libraries(grafikaGL ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
