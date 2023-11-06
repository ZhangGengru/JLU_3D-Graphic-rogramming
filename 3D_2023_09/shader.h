#pragma once
#include<string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace std;

class shader
{
public:
	shader(const char* vertexPath,const char* fragmentPath);
	void use() { glUseProgram(ID); }
	~shader();
private:
	GLuint ID;
	unsigned int vertex;//顶点着色器
	unsigned int fragment;//片段着色器
};

