#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h> 
#include <vector>
#include "Cube.h"
#include <iostream>

void Cube::Create() {

    float verts[] = {
        // positions          // colors          // texcoords
        // Back face (red)
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,

        // Front face (green)
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,

        // Left face (blue)
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,

        // Right face (yellow)
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  1.0f, 0.0f,

         // Bottom face (cyan)
         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f, 1.0f,
          0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  1.0f, 1.0f,
          0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  1.0f, 0.0f,
          0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  1.0f, 0.0f,
         -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,  0.0f, 0.0f,
         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f, 1.0f,

         // Top face (magenta)
         -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  0.0f, 1.0f,
          0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  1.0f, 1.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
          0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  1.0f, 0.0f,
         -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f, 0.0f,
         -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,  0.0f, 1.0f
    };


    const char* vertexSource = ReturnBasicVertexSource();

    //const char* fragmentSource = R"(
    //    #version 330 core
    //    out vec4 FragColor;

    //    in vec2 TexCoord;
    //    in vec3 vColor;

    //    uniform sampler2D u_texture;
    //    uniform float u_time;

    //    void main()
    //    {
    //        vec4 texColor = texture(u_texture, TexCoord);

    //        float r = 0.5 + 0.5 * sin(u_time * 0.5);
    //        float g = 0.5 + 0.5 * sin(u_time * 1.0);
    //        float b = 0.5 + 0.5 * sin(u_time * 1.5);

    //        vec3 animColor = vec3(r, g, b);

    //        // TEXTURE * VERTEX COLOR * ANIMATION
    //        vec3 finalColor = texColor.rgb * vColor * animColor;

    //        FragColor = vec4(finalColor, texColor.a);
    //    }
    //)";

    // Fragment shader
    const char* fragmentSource = R"(
            #version 330 core
in vec3 vPos;
out vec4 FragColor;

uniform float uTime;

vec3 palette(float t){
    vec3 a = vec3(1.218, 0.388, 0.668);
    vec3 b = vec3(1.028, 0.528, 0.308);
    vec3 c = vec3(1.0);
    vec3 d = vec3(0.0, 0.333, 0.667);
    return a + b * cos(6.28318*(c*t + d));
}

void main()
{
    float t = length(vPos) * 0.5 + uTime * 0.3;
    vec3 color = palette(t);
    FragColor = vec4(color, 1.0);
}
        )";

    // correct: assign to class members
    this->shaderProgram = CreateShaderProgram(vertexSource, fragmentSource);
    SetupBuffers(this->VAO, this->VBO, verts, 36);
    this->texture = LoadTexture("Resources/wall.jpg");
}

void Cube::Draw(glm::mat4 model)
{
    glUniform1f(glGetUniformLocation(shaderProgram, "uTime"), glfwGetTime());
    glUniform1i(glGetUniformLocation(shaderProgram, "u_texture"), 0);

    // MODEL matrix
    glUniformMatrix4fv(
        glGetUniformLocation(shaderProgram, "model"),
        1, GL_FALSE, glm::value_ptr(model)
    );

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}


void Cube::Destroy() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glDeleteTextures(1, &texture);
}
