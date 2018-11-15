cmake_minimum_required(VERSION 3.12)
project(ParticleSystem)

set(CMAKE_CXX_STANDARD 14)
set(OPENGL_LIBRARY_DIR "C:/Program Files/Common Files/MSVC/freeglut/lib")
set(GLUT_INCLUDE_DIR "C:/Program Files/Common Files/MSVC/freeglut/include")
# GLUT
find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})
if(NOT GLUT_FOUND)
    message(ERROR "GLUT not found!")
endif(NOT GLUT_FOUND)

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR "OPENGL not found!")
endif(NOT OPENGL_FOUND)

add_executable(ParticleSystem main.cpp Particle.cpp Particle.h utility.h Triple.cpp Triple.h)
target_link_libraries(ParticleSystem ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES})