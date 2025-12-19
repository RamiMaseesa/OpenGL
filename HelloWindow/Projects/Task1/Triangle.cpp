#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h> 
#include <vector>
#include "Triangle.h"
#include <iostream>

void Triangle::Create() {

    float verts[3 * 8] = { // X Y Z R G B U V 
        -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-left 
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right 
        0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f // top 
    };

    const char* vertexSource = ReturnBasicVertexSource();
    
    //    const char* vertexSource = R"(
    //#version 330 core
    //
    //layout (location = 0) in vec2 aPos;
    //layout (location = 1) in vec2 aTexCoord;
    //
    //out vec2 TexCoord;
    //
    //uniform mat4 transform;
    //
    //void main()
    //{
    //    gl_Position = transform * vec4(aPos, 0.0, 1.0);
    //    TexCoord = aTexCoord;
    //}
    //
    //    )";

    const char* fragmentSource = R"(
        #version 330 core
        out vec4 FragColor;
        in vec2 TexCoord;
        uniform sampler2D u_texture;
        uniform float u_time;
        void main() {
            vec4 texColor = texture(u_texture, TexCoord);

            float r = 0.5 + 0.5 * sin(u_time * 0.5);
            float g = 0.5 + 0.5 * sin(u_time * 1.0);
            float b = 0.5 + 0.5 * sin(u_time * 1.5);

            vec3 animColor = vec3(r, g, b);
            FragColor = vec4(texColor.rgb * animColor, texColor.a);
        }
    )";

    // correct: assign to class members
    this->shaderProgram = CreateShaderProgram(vertexSource, fragmentSource);
    SetupBuffers(this->VAO, this->VBO, verts, 3);
    this->texture = LoadTexture("Resources/wall.jpg");
}

void Triangle::Draw(glm::mat4 model)
{
    glUseProgram(shaderProgram);

    glUniform1f(glGetUniformLocation(shaderProgram, "u_time"), glfwGetTime());
    glUniform1i(glGetUniformLocation(shaderProgram, "u_texture"), 0);

    // MODEL matrix
    glUniformMatrix4fv(
        glGetUniformLocation(shaderProgram, "model"),
        1, GL_FALSE, glm::value_ptr(model)
    );

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}


void Triangle::Destroy() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glDeleteTextures(1, &texture);
}
