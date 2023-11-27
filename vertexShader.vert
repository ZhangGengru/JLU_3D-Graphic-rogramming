#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vColor;

out vec3 Color;//和片源着色器的输入变量类型，变量名完全一致
/////////////////////////////画雪花的矩阵
uniform mat4 rotate_Matrix;
uniform mat4 scale_Matrix;
uniform mat4 trans_Matrix;

//////////////////////////////////////////////随机X位置
uniform mat4 xPosition_transMatrix;
//////////////////////////////绘制掉落效果的矩阵。
uniform mat4 drop_transMatrix;//沿y轴下落矩阵
uniform mat4 drop_rotateMatrix;//旋转矩阵

void main()
{
	Color = vColor;
	vec4 position = vec4(vPos, 1.0);
	mat4 drawSnowFlake = scale_Matrix*rotate_Matrix*trans_Matrix;

	gl_Position = drop_transMatrix*xPosition_transMatrix*drop_rotateMatrix*drawSnowFlake*position; 
};