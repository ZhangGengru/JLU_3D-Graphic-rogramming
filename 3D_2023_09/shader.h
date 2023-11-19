#pragma once
#include<string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
using namespace std;

class Shader
{
public:
	const GLchar* ReadShader(const char* filename);
	Shader(const GLchar* vSourcePath, const GLchar* fSourcePath);
	void use() { glUseProgram(shaderProgram); }
	void end_use() { glUseProgram(0); }
	void setUniform(const GLchar* loc, float value);
	void setUniform(const GLchar* loc, float value1, float value2, float value3);
	void setUniform(const GLchar* loc, float value1, float value2, float value3, float value4);
	void setUniform(const GLchar* loc, glm::mat4 value);
	void setUniform(const GLchar* loc, glm::mat3 value);
	void setUniform(const GLchar* loc, glm::vec2 value);
	void setUniform(const GLchar* loc, glm::vec3 value);
	void setUniform(const GLchar* loc, glm::vec4 value);
	void setUniform(const GLchar* loc, int value);
	void setUniform(const char* name, GLuint value);
	void setUniform(const char* name, bool value);
	~Shader();
private:
	GLuint shaderProgram;
	unsigned int vertex;//顶点着色器
	unsigned int fragment;//片段着色器
};

