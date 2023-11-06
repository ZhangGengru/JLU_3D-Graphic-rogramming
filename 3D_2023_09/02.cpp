/*
    三角形绘制基础代码
	主要知识点：shader、VAO、VBO
	目的：
	（1）使用最简单的着色器方法绘制黑色背景的橙色三角形，方便慢慢改进。
	（2）程序可以通过ESC键退出。
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"
using namespace std;

GLuint vaoId;		//vertext array object句柄    
GLuint vboId;		//vertex buffer object句柄    

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) 
		glfwSetWindowShouldClose(window, GL_TRUE);
	//if((key == GLFW_KEY_LEFT_SHIFT||key == GLFW_KEY_Z) && action == GLFW_PRESS)
	bool keys[2] = { false,false };
	keys[0] = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;
	keys[1] = glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS;
	if (keys[0] && keys[1]) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}
	
//顶点着色器
const char* vertex_shader =
"#version 330 core\n"
"layout( location = 0 ) in vec3 vPosition;\n"
"void main() {\n"
"    gl_Position = vec4(vPosition, 1.0);\n"
"}";

//片元着色器
const char* fragment_shader =
"#version 330 core\n"
"out vec4 fColor;\n"
"void main() {\n"
"    fColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}";

void initModel()
{
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
	//分配了顶点数组对象VAO，返回n个未使用的对象名称，放在数组中，用作顶点数组
	//GLsizei n要生成顶点数组的数量, GLuint *arrays顶点数组对象的名称
	glGenVertexArrays(1, &vaoId);
	//绑定VAO
	glBindVertexArray(vaoId);
	//分配了缓冲对象VBO，返回n个未使用的对象名称，放在数组中，用作缓冲区对象
	glGenBuffers(1, &vboId); 
	//绑定VBO
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	
	//将顶点数据复制到缓冲的内存中
	//GLsizeiptr size要复制进缓冲的字节大小, const GLvoid *data源数据的地址, GLenum usage指定数据存储在GPU的哪个内存区域
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
	//设置index位置（着色器中的属性位置）对于的数据值
	//GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer
	//指定索引为0的顶点属性是一个由三个浮点值组成的向量，不进行归一化，步长为3个浮点数的大小，指向数组中第一个通用顶点属性的第一个组件。
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);  
	//启用顶点属性，这意味着OpenGL将使用索引0的通用顶点属性来渲染几何图形。
    glEnableVertexAttribArray(0);
	
    glBindBuffer(GL_ARRAY_BUFFER, 0);
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
		//rend();
		shader myShader(vertex_shader,fragment_shader);
		myShader.use();

		glBindVertexArray(vaoId);	
		glBindBuffer(GL_ARRAY_BUFFER, vboId);	
		glDrawArrays(GL_TRIANGLES, 0, 3);  

        glfwSwapBuffers(window); 
        glfwPollEvents(); 
    }
    glfwTerminate();
    return 0;
}