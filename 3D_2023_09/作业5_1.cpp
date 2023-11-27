#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

GLuint vaoId;		//vertext array object���    
GLuint vboId[2];		//vertex buffer object���   
GLuint eboId;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if ((key == GLFW_KEY_Z) && (mods & GLFW_MOD_SHIFT) && action != GLFW_RELEASE) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	// else if ((key == GLFW_KEY_Z) && !(mods & GLFW_MOD_SHIFT) && action != GLFW_RELEASE)
	else if ((key == GLFW_KEY_Z) && action != GLFW_RELEASE) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void initModel()
{	
	//����λ��
	const GLfloat onePiece[] = {
		0.06f, 0.03f, 0.0f,//0��
		0.3f , 0.03f, 0.0f,//1��
		0.50f, 0.20f, 0.0f,//2��
		0.54f, 0.20f, 0.0f,//3��
		0.35f, 0.03f, 0.0f,//4��
		0.54f, 0.03f, 0.0f,//5��
		0.65f, 0.18f, 0.0f,//6��
		0.71f, 0.18f, 0.0f,//7��
		0.59f, 0.04f, 0.0f,//8��
		0.71f,  0.04f, 0.0f,//9��
		0.8f, 0.0f,  0.0f //10��
	};
	//������ɫ
	const GLfloat color[] = {
		0.6f,0.6f,1.0f,
		0.6f,0.6f,1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		0.6f,0.6f,1.0f,
		0.6f,0.6f,1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		0.6f,0.6f,1.0f,
		0.6f,0.6f,1.0f,
		0.6f,0.6f,1.0f,
	};
	//��������VAO
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	//��������VBO
	glGenBuffers(2, vboId);
	//����λ��
	glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(onePiece), onePiece, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);
	//������ɫ
	glBindBuffer(GL_ARRAY_BUFFER, vboId[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);  				//ȡ��VAO��
	glBindBuffer(GL_ARRAY_BUFFER, 0);	//ȡ��vbo��
}

void rend()
{
	//������ɫ��
	Shader shader("../vertexShader.vert", "../fragmentShader.frag");
	//ʹ����ɫ��
	shader.use();
	glm::mat4 trans_Matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.03f, 0.0f, 0.0f));
	glm::mat4 rotate_Matrix = glm::mat4(1.0f);
	shader.setUniform("trans_Matrix", trans_Matrix);
	for (int i = 0; i < 6; i++)
	{
		rotate_Matrix = glm::rotate(rotate_Matrix, glm::radians(60.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		shader.setUniform("rotate_Matrix", rotate_Matrix);
		//ʹ��VAO�е����ݻ���
		glBindVertexArray(vaoId);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 11);
	}
	rotate_Matrix = glm::mat4(1.0f);
	rotate_Matrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, -1.0f, -1.0f));
	//rotate_Matrix = glm::translate(rotate_Matrix, glm::vec3(-0.05f, 0.0f, 0.0f));
	trans_Matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-0.08f, 0.0f, 0.0f));
	shader.setUniform("trans_Matrix", trans_Matrix);
	for (int i = 0; i < 6; i++)
	{
		rotate_Matrix = glm::rotate(rotate_Matrix, glm::radians(60.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		shader.setUniform("rotate_Matrix", rotate_Matrix);
		//ʹ��VAO�е����ݻ���
		glBindVertexArray(vaoId);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 11);
	}
	glBindVertexArray(0);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "snow", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwSetKeyCallback(window, keyCallback);

	initModel();

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		rend();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}