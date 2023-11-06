/*
    利用GLFW和Glad创建一个窗口
    */
#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include<iostream>

//在窗口大小改变时调整视口大小
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    //调整窗口大小
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    //初始化GLFW，成功返回GLFW_TRUE, 失败返回CLFW_FALSE
    //在使用GLFW的任何功能之前都需要初始化GLFW，GLFW会检查系统是否支持OpenGL相关的功能
    glfwInit(); 
    //glfwWindowHint函数用于设置OpenGL的版本号，这里设置为3.3
    //主版本号：
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //次版本号：
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //用于设置OpenGL上下文模式。
    //设置为核心模式
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   
    
    //创建一个窗口对象。GLFWwindow* glfwCreateWindow(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
    //                返回一个窗口                       宽        高         窗口标题        监视器，用于设置全屏模式     共享资源，NULL表示不共享上下文
    //                                                                                          NULL表示窗口模式       
    //GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Core", glfwGetPrimaryMonitor(), NULL); 创建一个全屏对象
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Core", NULL, NULL);
   
    //判断窗口是否创建成功
    if (window == NULL)  
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        //用于终止GLFW，释放资源
        glfwTerminate();
        return -1;
    }
    //设置window的上下文为当前上下文
    glfwMakeContextCurrent(window);  

    //gladLoadGLLoader加载OpenGL的指针，接受一个GLADloadproc类型的参数
    //glfwGetProcAddress获取OpenGL函数指针。
    //初始化GLAD，GLAD是用来管理OpenGL指针的，所以在调用任何OpenGL的函数之前需要初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //设置窗口的大小和位置，接收4个参数
    //glViewport (GLint x, GLint y, GLsizei width, GLsizei height);
    //x:左下角的x坐标 y:左下角y左坐标 后面两个参数像素为单位。
    glViewport(0, 0, 800, 600);

    //注册窗口大小改变的回调函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    
    //glfwWindowShouldClose用于检查窗口是否关闭
    //循环渲染
    while (!glfwWindowShouldClose(window)) 
    {
        //检查是否ESC
        processInput(window);
        //用于设置清空屏幕所用的颜色
        //glClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
        //r g b即透明度
        glClearColor(0.9f, 0.8f, 0.4f, 1.0f);
        //清除颜色缓冲区。参数用于指定要清除的缓冲区
        glClear(GL_COLOR_BUFFER_BIT);
        //用于交换指定窗口的前后缓冲区
        /*
        在使用OpenGL时，通常需要使用双缓冲技术来避免渲染过程中的闪烁问题。
        双缓冲技术使用两个缓冲区来存储图像，一个用于显示，一个用于渲染。
        当渲染完成后，将渲染缓冲区中的图像复制到显示缓冲区中，从而避免了闪烁问题。
        */
        glfwSwapBuffers(window); 
        //检查是否有事件触发，如键盘输入、鼠标移动
        glfwPollEvents(); 
    }
    glfwTerminate();
    return 0;
}