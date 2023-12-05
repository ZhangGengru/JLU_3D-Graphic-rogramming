#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <vector>
#include "stb_image.h"
#include "shader.h"

GLuint vaoId[2];
GLuint vboId[2];
GLuint backgountvboId[2];
GLuint eboId;
GLuint textureId[2];

struct CubePosition
{
	float x;
	float y;
	float z;
	float rotateRate;
	glm::vec3 rotateAxis;
};

std::vector<CubePosition> cubePositions = {
	{0.0f, 0.0f, 8.0f, 1.0f,glm::vec3(0.0f,1.0f,0.0f)},
	{2.0f, 1.0f, 5.0f, 4.0f,glm::vec3(0.0f,1.0f,0.0f)},
	{-1.0f,0.5f, 6.0f, 100.0f,glm::vec3(1.0f,0.0f,0.0f)},
	{3.0f, 4.0f, 3.0f,50.0f,glm::vec3(1.0f,1.0f,0.0f)},
	{1.0f,5.0f, -10.0f,20.0f,glm::vec3(0.0f,1.0f,0.0f)},
	{-1.0f,2.5f,0.0f,30.0f,glm::vec3(0.0f,1.0f,1.0f)}
	
};

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
	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;

	glGenTextures(2, textureId);
	//第一个纹理
	glBindTexture(GL_TEXTURE_2D, textureId[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data = stbi_load("../src/boxF.png",&width,&height,&nrChannels,0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,
			GL_UNSIGNED_BYTE,data);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	//第二个纹理
	glBindTexture(GL_TEXTURE_2D, textureId[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	data = stbi_load("../src/sekiro.png", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
			GL_UNSIGNED_BYTE, data);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	//顶点位置信息
	const GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5,
		0.5f, -0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		-0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		
		-0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f,-0.5f,
		-0.5f, -0.5f,-0.5f,
		-0.5f, -0.5f,-0.5f,
		-0.5f, -0.5f,0.5f,
		-0.5f, 0.5f,0.5f,

		0.5f, 0.5f,0.5f,
		0.5f, 0.5f,-0.5f,
		0.5f, -0.5f,-0.5f,
		0.5f, -0.5f,-0.5f,
		0.5f, -0.5f,0.5f,
		0.5f, 0.5f,0.5f,

		-0.5f, -0.5f,-0.5f,
		0.5f, -0.5f,-0.5f,
		0.5f, -0.5f,0.5f,
		0.5f, -0.5f,0.5f,
		-0.5f, -0.5f,0.5f,
		-0.5f, -0.5f,-0.5f,

		-0.5f, 0.5f,-0.5f,
		0.5f, 0.5f,-0.5f,
		0.5f, 0.5f,0.5f,
		0.5f, 0.5f,0.5f,
		-0.5f, 0.5f,0.5f,
		-0.5f, 0.5f,-0.5f
	};
	//纹理坐标
	const GLfloat texture[] = {
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,

		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
			
		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		1.0f, 0.0f,
		1.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,

		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 0.0f,
		0.0f, 1.0f,
	};

	glGenVertexArrays(2,vaoId);
	glGenBuffers(2, vboId);

	glBindVertexArray(vaoId[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vboId[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(texture), texture, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

	const GLfloat background[] = {
		-15.0f,15.0f,0.0f,//0
		-15.0f,-15.0f,0.0f,//1
		15.0f,-15.0f,0.0f,//2
		15.0f,15.0f,0.0f,//3
	};
	const GLfloat Backtextrue[] = {
		1.0f,1.0f,
		1.0f,0.0f,
		0.0f,0.0f,
		0.0f,1.0f
	};
	unsigned int indices[] = {
		0,1,3,
		1,2,3
	};
	glBindVertexArray(vaoId[1]);
	glGenBuffers(2, backgountvboId);

	glBindBuffer(GL_ARRAY_BUFFER, backgountvboId[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(background), background, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, backgountvboId[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Backtextrue), Backtextrue, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);


	glGenBuffers(1, &eboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void drawCube(Shader& Cube)
{
	//绑定纹理
	Cube.use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureId[1]);

	//设置uniform
	glUniform1i(glGetUniformLocation(Cube.getshaderProgramId(), "myTexture"), 0);
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 13.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);


	Cube.setUniform("model", model);
	Cube.setUniform("view", view);
	Cube.setUniform("projection",projection);


	
}
void MoveCube(Shader& Cube)
{
	glm::mat4 model = glm::mat4(1.0f);
	float changeValue = glfwGetTime();
	for (const auto r:cubePositions)
	{
		model = glm::translate(glm::mat4(1.0f), glm::vec3(r.x, r.y, r.z));
		Cube.setUniform("model",model);
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f),glm::radians(changeValue*r.rotateRate),r.rotateAxis);
		Cube.setUniform("rotation", rotation);
		glBindVertexArray(vaoId[0]);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	glBindVertexArray(0);
}
void drawBackground(Shader& Background)
{
	Background.use();
	//绑定纹理
	

	glUniform1i(glGetUniformLocation(Background.getshaderProgramId(), "myTexture"), 1);
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,-15.0f));
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 13.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);

	Background.setUniform("model", model);
	Background.setUniform("view", view);
	Background.setUniform("projection", projection);

	glBindVertexArray(vaoId[1]);
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

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, keyCallback);

	initModel();
	Shader Cube("../绘制立方体顶点着色器.vert", "../绘制立方体片段着色器.frag");
	Shader BackGround("../绘制背景顶点着色器.vert", "../绘制背景片段着色器.frag");
	glEnable(GL_DEPTH_TEST); // 开启深度检测
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		drawCube(Cube);
		MoveCube(Cube);
		drawBackground(BackGround);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(2, vaoId);
	glDeleteBuffers(2, vboId);

	glfwTerminate();
	return 0;
}
