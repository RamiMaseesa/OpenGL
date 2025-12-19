#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include"Projects/3DObjects/Cube.h"
#include "Projects/3DCamera/Camera.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void Go3D(unsigned int shaderProgram, Camera camera);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // static vars
    // -----------
    srand(static_cast<unsigned int>(time(0)));

    Camera camera(SCR_WIDTH, SCR_HEIGHT);
    glfwSetWindowUserPointer(window, &camera);
    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double x, double y) {
        Camera* cam = static_cast<Camera*>(glfwGetWindowUserPointer(window));
        cam->mouse_callback(window, x, y);
        });
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // vars
    // ----
    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 trans2 = glm::mat4(1.0f);

    float rotationAngle = 0.0f;
    bool addAngle = true;

    int size = 10;
    int cubeCount = size * size * size;
    std::vector<Cube> cubes;

    // create the cubes
    for (int i = 0; i < cubeCount; i++) {
        Cube cube;
        cube.Create();
        cubes.push_back(cube);
    }
    glm::mat4 transCube = glm::mat4(1.0f);

    std::vector<glm::mat4> cubeModels;
    cubeModels.reserve(cubeCount); // reserve space for cubeCount cubes

    
    float spacing = 1.5f; // distance between cubes

    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            for (int z = 0; z < size; z++) {
                glm::mat4 model = glm::mat4(1.0f);

                glm::vec3 position(
                    (x - size / 2) * spacing,
                    (y - size / 2) * spacing,
                    (z - size / 2) * spacing
                );

                model = glm::translate(model, position);
                cubeModels.push_back(model);
            }
        }
    }

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);
        camera.processInput(window);

        // render
        // ------
        
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // rotation
        if (addAngle) {
            trans = glm::rotate(trans, glm::radians(1.0f), glm::vec3(1.0, 1.0, 1.0));
            rotationAngle += 1.0;

            if (rotationAngle == 360) addAngle = false;
        }
        else {
            trans = glm::rotate(trans, glm::radians(1.0f), glm::vec3(1.0, -1.0, -1.0));
            rotationAngle -= 1.0;

            if (rotationAngle == 0) addAngle = true;
        }

        float scaleAmount = 1.0f + 0.2f * sin(glfwGetTime()); // oscillates 0.8 -> 1.2
        glm::mat4 trans2 = glm::scale(glm::mat4(1.0f), glm::vec3(scaleAmount));

        // draw
        // ----
        for (int i = 0; i < cubeModels.size(); i++) {
            glUseProgram(cubes[i].shaderProgram); // assuming you have cubeCount Cube objects
            Go3D(cubes[i].shaderProgram, camera);

            cubes[i].Draw(cubeModels[i] * trans);
        }

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // free all the vars I made
    // ------------------------


    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();

    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void Go3D(unsigned int shaderProgram, Camera camera)
{
    glUseProgram(shaderProgram);

    glm::mat4 view = glm::lookAt(
        camera.cameraPos,
        camera.cameraPos + camera.cameraFront,
        camera.cameraUp
    );

    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        (float)SCR_WIDTH / SCR_HEIGHT,
        0.1f, 100.0f
    );

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"),
        1, GL_FALSE, glm::value_ptr(view));

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"),
        1, GL_FALSE, glm::value_ptr(projection));
}
