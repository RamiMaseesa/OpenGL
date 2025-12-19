#pragma once
#include <vector>

#include <../../HelperFunctions/Shader/ShaderUtil.h>

#include <../../HelperFunctions/glm/glm.hpp>
#include <../../HelperFunctions/glm/gtc/matrix_transform.hpp>
#include <../../HelperFunctions/glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

class Camera {
public:
    glm::vec3 cameraPos, cameraFront, cameraUp;
    float yaw, pitch, lastX, lastY, deltaTime, lastFrame, cameraSpeed;
    bool firstMouse;

    Camera(float width, float height);

    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void processInput(GLFWwindow* window);
};