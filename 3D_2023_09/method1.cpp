/*
    三角形绘制
	主要知识点：shader、VAO、VBO
	目的：
	（1）使用Shader类绘制三角形。
	（2）程序可以通过键盘ESC和z/Z（shift+z）键退出。
	
	vertexShader.glsl：顶点着色器
	fragmentShader.glsl：片元着色器
	
*/
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

GLuint vaoId;		//vertext array object句柄    
GLuint vboId;		//vertex buffer object句柄    

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
	//两个三角形的顶点
	float vertices[] = {
		 //第一个三角形      颜色
		-1.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.0f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		 //第二个三角形      颜色
		 0.1f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		 1.0f,  0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		 0.1f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f
	};
	//创建并绑定VAO
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	//创建并绑定VBO
	glGenBuffers(1, &vboId); 
	glBindBuffer(GL_ARRAY_BUFFER, vboId); 
	//将顶点数据复制到VBO中
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);	//取消vbo绑定
    glBindVertexArray(0);  				//取消VAO绑定
}

void rend()
{
	//创建着色器
	Shader shader("../vertexShader.vert", "../fragmentShader.frag");
	//使用着色器
	shader.use();

	//使用VAO中的数据绘制
	glBindVertexArray(vaoId);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
}

int main()
{
    glfwInit(); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "method 1", NULL, NULL);
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