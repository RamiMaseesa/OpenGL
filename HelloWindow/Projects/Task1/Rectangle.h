#pragma once
#include <vector>

#include <../../HelperFunctions/Shader/ShaderUtil.h>

#include <../../HelperFunctions/glm/glm.hpp>
#include <../../HelperFunctions/glm/gtc/matrix_transform.hpp>
#include <../../HelperFunctions/glm/gtc/type_ptr.hpp>

class FullScreenRectangle {
public:
    unsigned int VAO, VBO, texture, shaderProgram;

    void Create();
    void Draw(glm::mat4);
    void Destroy();
};