#pragma once
#include <vector>

#include <../../HelperFunctions/Shader/ShaderUtil.h>

#include <../../HelperFunctions/glm/glm.hpp>
#include <../../HelperFunctions/glm/gtc/matrix_transform.hpp>
#include <../../HelperFunctions/glm/gtc/type_ptr.hpp>

class Cube {
public:
    unsigned int VAO, VBO, texture, shaderProgram;

    void Create();
    void Create(unsigned int VAO, unsigned int VBO, unsigned int texture, unsigned int shaderProgram);
    void Draw(glm::mat4);
    void Destroy();
};