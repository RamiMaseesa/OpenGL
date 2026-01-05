#pragma once
#include <vector>

#include <../../HelperFunctions/Shader/ShaderUtil.h>

#include <../../HelperFunctions/glm/glm.hpp>
#include <../../HelperFunctions/glm/gtc/matrix_transform.hpp>
#include <../../HelperFunctions/glm/gtc/type_ptr.hpp>

class Cube {
public:
    unsigned int VAO, VBO, instanceVBO, texture, shaderProgram;

    void Create();
    void CreateInstance(unsigned int VAO, unsigned int VBO, unsigned int shaderProgram,
               unsigned int texture, std::vector<glm::mat4>& cubeModels);
    void Draw(glm::mat4);
    void DrawInstanced(int instanceCount);
    void Destroy();
};