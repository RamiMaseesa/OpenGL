#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <../../HelperFunctions/Textures/stb_image.h>

unsigned int LoadTexture(const char* path) {
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data) {
		GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(data);
	}
	else {
		std::cout << "Failed to load texture: " << path << std::endl;
	}

	return texture;
}

float* GenerateRandomVertices(unsigned int amountOfVertecies) {
	float* verts = new float[amountOfVertecies * 3];

	for (int i = 0; i < (amountOfVertecies * 3); i++) {
		if ((i + 1) % 3 == 0)
			verts[i] = 0;
		else
			verts[i] = ((float)rand() / RAND_MAX) * 2.0f - 1.0f;
		std::cout << verts[i] << std::endl;
	}

	return verts;
}

unsigned int CompileShader(unsigned int type, const char* source) {
	unsigned int shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	return shader;
}

unsigned int CreateShaderProgram(const char* vertexSource, const char* fragmentSource) {
	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

	unsigned int program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	int success;
	char infoLog[512];
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}

void SetupBuffers(unsigned int& VAO, unsigned int& VBO, float* vertices, unsigned int numVertices) {
	glGenVertexArrays(1, &VAO);
	if (VAO == 0) {
		std::cerr << "[ERROR] Failed to generate VAO!" << std::endl;
		return;
	}
	glGenBuffers(1, &VBO);
	if (VBO == 0) {
		std::cerr << "[ERROR] Failed to generate VBO!" << std::endl;
		return;
	}

	glBindVertexArray(VAO);
	GLenum err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "[ERROR] glBindVertexArray failed with code: " << err << std::endl;
		return;
	}
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "[ERROR] glBindBuffer failed with code: " << err << std::endl;
		return;
	}

	// 3 vertices * 8 floats per vertex
	glBufferData(GL_ARRAY_BUFFER, numVertices * 8 * sizeof(float), vertices, GL_STATIC_DRAW);
	err = glGetError();
	if (err != GL_NO_ERROR) {
		std::cerr << "[ERROR] glBufferData failed with code: " << err << std::endl;
		return;
	}

	int stride = 8 * sizeof(float);
	std::cerr << "stride value: " << stride << std::endl;

	// Position (location = 0)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
	glEnableVertexAttribArray(0);

	// Color (location = 1)
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// UV (location = 2)
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

const char* ReturnBasicVertexSource() {
	return R"(
        #version 330 core

        layout(location = 0) in vec3 aPos;
        layout(location = 1) in vec3 aColor;
        layout(location = 2) in vec2 aTex;
        
		out vec2 TexCoord;
		out vec3 vColor;

		out vec3 vPos;
		
		uniform mat4 model;
		uniform mat4 view;
		uniform mat4 projection;
		
        void main() {
            gl_Position = projection * view * model * vec4(aPos, 1.0);
            TexCoord = vec2(aTex.x, aTex.y);
			vColor = aColor;
			
        }
    )";
}