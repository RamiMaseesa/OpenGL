#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <../../HelperFunctions/glm/glm.hpp>
#include <iostream>
#include "Rectangle.h"

    void FullScreenRectangle::Create() {
        // Fullscreen quad (two triangles)
        float vertices[] = {
            // X, Y, Z
            1.f,  1.f, 0.0f,
            1.f, -1.f, 0.0f,
           -1.f, -1.f, 0.0f,

           -1.f, -1.f, 0.0f,
           -1.f,  1.f, 0.0f,
            1.f,  1.f, 0.0f
        };

        // Vertex shader
        const char* vertexSource = R"(
            #version 330 core
            layout(location = 0) in vec3 aPos;
            out vec3 vPos;

            void main() {
                gl_Position = vec4(aPos, 1.0);
                vPos = aPos;
            }
        )";

        // Fragment shader
        const char* fragmentSource = R"(
            #version 330 core
            in vec3 vPos;
            out vec4 FragColor;
            uniform float uTime;
            uniform vec2 iResolution;

            float speed = 3.0;

            vec3 palette(float t){
                vec3 a = vec3(1.218, 0.388, 0.668);
                vec3 b = vec3(1.028, 0.528, 0.308);
                vec3 c = vec3(1.0);
                vec3 d = vec3(0.0, 0.333, 0.667);
                return a + b * cos(6.28318*(c*t + d));
            }

            void main() {
                vec2 uv = (gl_FragCoord.xy * 2.0 - iResolution.xy) / iResolution.y;
                vec2 uv0 = uv;
                vec3 finalColor = vec3(0.0);

                for (float i = 0.0; i < (2.0 + (uTime * 0.1)); i++) {
                    uv = fract(uv * 1.5) - 0.5;
                    float d = length(uv) * exp(-length(uv0 * 0.4));
                    vec3 col = palette(length(uv0 * 0.6) + i * -0.4 - uTime * 0.0);
                    d = sin(d * 12.0 + uTime * speed) / 8.0;
                    d = abs(d);
                    d = 0.01 / d;
                    finalColor += col * d;
                }
                FragColor = vec4(finalColor, 1.0);
            }
        )";

        shaderProgram = CreateShaderProgram(vertexSource, fragmentSource);

        // Setup VAO/VBO
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void FullScreenRectangle::Draw(glm::mat4 model)
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
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }


    void FullScreenRectangle::Destroy() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteProgram(shaderProgram);
        glDeleteTextures(1, &texture);
    }

