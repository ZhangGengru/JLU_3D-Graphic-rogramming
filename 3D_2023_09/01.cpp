/*
    ����GLFW��Glad����һ������
    */
#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>

//�ڴ��ڴ�С�ı�ʱ�����ӿڴ�С
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    //�������ڴ�С
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    //��ʼ��GLFW���ɹ�����GLFW_TRUE, ʧ�ܷ���CLFW_FALSE
    //��ʹ��GLFW���κι���֮ǰ����Ҫ��ʼ��GLFW��GLFW����ϵͳ�Ƿ�֧��OpenGL��صĹ���
    glfwInit(); 
    //glfwWindowHint������������OpenGL�İ汾�ţ���������Ϊ3.3
    //���汾�ţ�
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //�ΰ汾�ţ�
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //��������OpenGL������ģʽ��
    //����Ϊ����ģʽ
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   
    
    //����һ�����ڶ���GLFWwindow* glfwCreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
    //                ����һ������                       ��        ��         ���ڱ���        ����������������ȫ��ģʽ     ������Դ��NULL��ʾ������������
    //                                                                                          NULL��ʾ����ģʽ       
    //GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Core", glfwGetPrimaryMonitor(), NULL); ����һ��ȫ������
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Core", NULL, NULL);
   
    //�жϴ����Ƿ񴴽��ɹ�
    if (window == NULL)  
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        //������ֹGLFW���ͷ���Դ
        glfwTerminate();
        return -1;
    }
    //����window��������Ϊ��ǰ������
    glfwMakeContextCurrent(window);  

    //gladLoadGLLoader����OpenGL��ָ�룬����һ��GLADloadproc���͵Ĳ���
    //glfwGetProcAddress��ȡOpenGL����ָ�롣
    //��ʼ��GLAD��GLAD����������OpenGLָ��ģ������ڵ����κ�OpenGL�ĺ���֮ǰ��Ҫ��ʼ��GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //���ô��ڵĴ�С��λ�ã�����4������
    //glViewport (GLint x, GLint y, GLsizei width, GLsizei height);
    //x:���½ǵ�x���� y:���½�y������ ����������������Ϊ��λ��
    glViewport(0, 0, 800, 600);

    //ע�ᴰ�ڴ�С�ı�Ļص�����
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    
    //glfwWindowShouldClose���ڼ�鴰���Ƿ�ر�
    //ѭ����Ⱦ
    while (!glfwWindowShouldClose(window)) 
    {
        //����Ƿ�ESC
        processInput(window);
        //�������������Ļ���õ���ɫ
        //glClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
        //r g b��͸����
        glClearColor(0.9f, 0.8f, 0.4f, 1.0f);
        //�����ɫ����������������ָ��Ҫ����Ļ�����
        glClear(GL_COLOR_BUFFER_BIT);
        //���ڽ���ָ�����ڵ�ǰ�󻺳���
        /*
        ��ʹ��OpenGLʱ��ͨ����Ҫʹ��˫���弼����������Ⱦ�����е���˸���⡣
        ˫���弼��ʹ���������������洢ͼ��һ��������ʾ��һ��������Ⱦ��
        ����Ⱦ��ɺ󣬽���Ⱦ�������е�ͼ���Ƶ���ʾ�������У��Ӷ���������˸���⡣
        */
        glfwSwapBuffers(window); 
        //����Ƿ����¼���������������롢����ƶ�
        glfwPollEvents(); 
    }
    glfwTerminate();
    return 0;
}