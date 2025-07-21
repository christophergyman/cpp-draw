// shaders.h
#ifndef SHADERS_H
#define SHADERS_H

#include "glad/glad.h"

struct Shaders {
    unsigned int shaderProgram;
    unsigned int VAO;
    unsigned int VBO;
};

Shaders init_and_compile_shaders();

#endif
