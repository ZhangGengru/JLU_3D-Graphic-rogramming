#pragma once
#include<string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
using namespace std;

class Shader
{
public:
	const GLchar* ReadShader(const char* filename);
	Shader(const GLchar* vSourcePath, const GLchar* fSourcePath);
	void use() { glUseProgram(shaderProgram); }
	void end_use() { glUseProgram(0); }
	~Shader();
private:
	GLuint shaderProgram;
	unsigned int vertex;//������ɫ��
	unsigned int fragment;//Ƭ����ɫ��
};

