#include "shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

using namespace std;


const GLchar* Shader::ReadShader(const char* filename)
{
	FILE* infile = NULL;
	fopen_s(&infile, filename, "rb");
	if (!infile) {
		std::cerr << "Unable to open file '" << filename << "'" << std::endl;
		return NULL;
	}
	fseek(infile, 0, SEEK_END);
	size_t len = ftell(infile);
	fseek(infile, 0, SEEK_SET);
	GLchar* source = new GLchar[len + 1];
	fread(source, 1, len, infile);
	fclose(infile);
	source[len] = '\0';
	return const_cast<const GLchar*>(source);
}

Shader::Shader(const GLchar* vSourcePath, const GLchar* fSourcePath)
{
	string vertexCode = ReadShader(vSourcePath);
	string fragmentCode = ReadShader(fSourcePath);
	
	//shader�Ķ��뼰����
	//ת��GLchar����
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	//������ɫ������
	GLint success;
	GLchar* infoLog = new GLchar[512];
	//������ɫ��
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS,&success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << endl;
	}

	//Ƭ����ɫ��
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << endl;
	}

	//shader����
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertex);
	glAttachShader(shaderProgram, fragment);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}
void Shader::setUniform(const GLchar* loc, float value) {
	glUniform1f(glGetUniformLocation(shaderProgram, loc), value);
}

void Shader::setUniform(const GLchar* loc, float value1, float value2, float value3) {
	glUniform3f(glGetUniformLocation(shaderProgram, loc), value1, value2, value3);
}

void Shader::setUniform(const GLchar* loc, float value1, float value2, float value3, float value4) {
	glUniform4f(glGetUniformLocation(shaderProgram, loc), value1, value2, value3, value4);
}

void Shader::setUniform(const GLchar* loc, glm::mat4 value) {
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, loc), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setUniform(const GLchar* loc, glm::mat3 value) {
	glUniformMatrix3fv(glGetUniformLocation(shaderProgram, loc), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setUniform(const GLchar* loc, glm::vec2 value) {
	glUniform3fv(glGetUniformLocation(shaderProgram, loc), 1, glm::value_ptr(value));
}

void Shader::setUniform(const GLchar* loc, glm::vec3 value) {
	glUniform3fv(glGetUniformLocation(shaderProgram, loc), 1, glm::value_ptr(value));
}

void Shader::setUniform(const GLchar* loc, glm::vec4 value) {
	glUniform3fv(glGetUniformLocation(shaderProgram, loc), 1, glm::value_ptr(value));
}

void Shader::setUniform(const GLchar* loc, int value) {
	glUniform1i(glGetUniformLocation(shaderProgram, loc), value);
}

void Shader::setUniform(const char* loc, GLuint value) {
	glUniform1ui(glGetUniformLocation(shaderProgram, loc), value);
}

void Shader::setUniform(const char* loc, bool value) {
	glUniform1i(glGetUniformLocation(shaderProgram, loc), value);
}
Shader::~Shader()
{
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}
