/*
    �����λ���
	��Ҫ֪ʶ�㣺shader��VAO��VBO
	Ŀ�ģ�
	��1��ʹ��Shader����������Ρ�
	��2���������ͨ������ESC��z/Z��shift+z�����˳���
	
	vertexShader.glsl��������ɫ��
	fragmentShader.glsl��ƬԪ��ɫ��
	
*/
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

GLuint vaoId[2];		//vertext array object���    
GLuint vboId[2];		//vertex buffer object���   

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
	float vertices1[] = {
		-1.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f
	};
	
	float vertices2[] = {
		 0.1f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 1.0f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.1f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f
	};
	glGenVertexArrays(2,vaoId);
	glGenBuffers(2, vboId);

	//��һ��VAO
	glBindVertexArray(vaoId[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	//�ڶ���VAO
	glBindVertexArray(vaoId[1]);
	glBindBuffer(GL_ARRAY_BUFFER, vboId[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(0 * sizeof(float)));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);



    glBindBuffer(GL_ARRAY_BUFFER, 0);	//ȡ��vbo��
    glBindVertexArray(0);  				//ȡ��VAO��
}

void rend()
{
	//������ɫ��
	Shader shader("../vertexShader.vert", "../fragmentShader.frag");
	//ʹ����ɫ��
	shader.use();

	//ʹ�õ�һ��VAO�е����ݻ���
	glBindVertexArray(vaoId[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	//ʹ�õڶ���VAO�е����ݻ���
	glBindVertexArray(vaoId[1]);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
}

int main()
{
    glfwInit(); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Core", NULL, NULL);
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