#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

GLuint vaoId;		//vertext array object���    
GLuint vboId;		//vertex buffer object���   
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
	else if ((key == GLFW_KEY_Z) && action != GLFW_RELEASE){
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void initModel()
{
	const GLfloat vertices[] = {
		0.5f, 0.5f, 0.0f,//0�ŵ�
	   -0.5f, 0.5f, 0.0f,//1�ŵ�
		0.5f,-0.5f, 0.0f,//2�ŵ�
	   -0.5f,-0.5f, 0.0f //3�ŵ�
	};
	unsigned int indices[] = {
		0,1,2,	//��һ��������
		2,1,3	//�ڶ���������
	};
	//��������VAO
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	//��������VBO
	glGenBuffers(1, &vboId); 
	glBindBuffer(GL_ARRAY_BUFFER, vboId); 
	//���������ݸ��Ƶ�VBO��
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &eboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	

    glBindVertexArray(0);  				//ȡ��VAO��
    glBindBuffer(GL_ARRAY_BUFFER, 0);	//ȡ��vbo��
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);//ȡ��EBO��
}

void rend()
{
	//������ɫ��
	Shader shader("../vertexShader.vert", "../fragmentShader.frag");
	//ʹ����ɫ��
	shader.use();

	
	//ʹ��VAO�е����ݻ���
	glBindVertexArray(vaoId);
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
	glBindVertexArray(0);
}

int main()
{
    glfwInit(); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	
    GLFWwindow* window = glfwCreateWindow(800, 600, "Rectangle", NULL, NULL);
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
		glLineWidth(2.5f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glPolygonMode(GL_FRONT, GL_LINE);
		rend();
        glfwSwapBuffers(window); 
        glfwPollEvents(); 
    }
    glfwTerminate();
    return 0;
}