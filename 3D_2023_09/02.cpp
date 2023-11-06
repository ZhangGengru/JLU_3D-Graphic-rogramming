/*
    �����λ��ƻ�������
	��Ҫ֪ʶ�㣺shader��VAO��VBO
	Ŀ�ģ�
	��1��ʹ����򵥵���ɫ���������ƺ�ɫ�����ĳ�ɫ�����Σ����������Ľ���
	��2���������ͨ��ESC���˳���
*/

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"
using namespace std;

GLuint vaoId;		//vertext array object���    
GLuint vboId;		//vertex buffer object���    

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
	
//������ɫ��
const char* vertex_shader =
"#version 330 core\n"
"layout( location = 0 ) in vec3 vPosition;\n"
"void main() {\n"
"    gl_Position = vec4(vPosition, 1.0);\n"
"}";

//ƬԪ��ɫ��
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
	//�����˶����������VAO������n��δʹ�õĶ������ƣ����������У�������������
	//GLsizei nҪ���ɶ������������, GLuint *arrays����������������
	glGenVertexArrays(1, &vaoId);
	//��VAO
	glBindVertexArray(vaoId);
	//�����˻������VBO������n��δʹ�õĶ������ƣ����������У���������������
	glGenBuffers(1, &vboId); 
	//��VBO
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	
	//���������ݸ��Ƶ�������ڴ���
	//GLsizeiptr sizeҪ���ƽ�������ֽڴ�С, const GLvoid *dataԴ���ݵĵ�ַ, GLenum usageָ�����ݴ洢��GPU���ĸ��ڴ�����
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
	//����indexλ�ã���ɫ���е�����λ�ã����ڵ�����ֵ
	//GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid *pointer
	//ָ������Ϊ0�Ķ���������һ������������ֵ��ɵ������������й�һ��������Ϊ3���������Ĵ�С��ָ�������е�һ��ͨ�ö������Եĵ�һ�������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);  
	//���ö������ԣ�����ζ��OpenGL��ʹ������0��ͨ�ö�����������Ⱦ����ͼ�Ρ�
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