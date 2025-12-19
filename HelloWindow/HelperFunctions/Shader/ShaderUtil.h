#pragma once

struct ObjectData {
	unsigned int VAO;
	unsigned int VBO;
	unsigned int shaderProgram;
	unsigned int texture;
};

unsigned int LoadTexture(const char* path);
float* GenerateRandomVertices(unsigned int);
unsigned int CompileShader(unsigned int type, const char* source);
unsigned int CreateShaderProgram(const char* vertexSource, const char* fragmentSource);
void SetupBuffers(unsigned int& VAO, unsigned int& VBO, float* vertices, unsigned int numVertices);
const char* ReturnBasicVertexSource();