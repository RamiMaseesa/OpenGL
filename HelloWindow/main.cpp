#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include"Projects/3DObjects/Cube.h"




void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void Go3D(unsigned int shaderProgram);

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

    // vars
    // ----
    glm::mat4 trans = glm::mat4(1.0f);

    float rotationAngle = 0.0f;
    bool addAngle = true;

    std::vector<Cube> cubes;

    // create the cubes
    for (int i = 0; i < 27; i++) {
        Cube cube;
        cube.Create();
        cubes.push_back(cube);
    }
    glm::mat4 transCube = glm::mat4(1.0f);

    std::vector<glm::mat4> cubeModels;
    cubeModels.reserve(27); // reserve space for 27 cubes

    float spacing = 1.5f; // distance between cubes

    // 3x3x3 nested loops
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            for (int z = 0; z < 3; z++) {
                glm::mat4 model = glm::mat4(1.0f); // identity
                // center the cube formation around the origin
                glm::vec3 position = glm::vec3(
                    (x - 1) * spacing,   // -1, 0, 1
                    (y - 1) * spacing,   // -1, 0, 1
                    (z - 2) * spacing    // -1, 0, 1
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

        // draw
        // ----

        for (int i = 0; i < cubeModels.size(); i++) {
            glUseProgram(cubes[i].shaderProgram); // assuming you have 27 Cube objects
            Go3D(cubes[i].shaderProgram);
            cubes[i].Draw(cubeModels[i]);
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

void Go3D(unsigned int shaderProgram)
{
    glUseProgram(shaderProgram);

    glm::mat4 view = glm::translate(glm::mat4(1.0f),
        glm::vec3(0.0f, 0.0f, -3.0f));

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
