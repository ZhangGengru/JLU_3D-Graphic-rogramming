#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vColor;

out vec3 Color;//��ƬԴ��ɫ��������������ͣ���������ȫһ��
/////////////////////////////��ѩ���ľ���
uniform mat4 rotate_Matrix;
uniform mat4 scale_Matrix;
uniform mat4 trans_Matrix;

//////////////////////////////////////////////���Xλ��
uniform mat4 xPosition_transMatrix;
//////////////////////////////���Ƶ���Ч���ľ���
uniform mat4 drop_transMatrix;//��y���������
uniform mat4 drop_rotateMatrix;//��ת����

void main()
{
	Color = vColor;
	vec4 position = vec4(vPos, 1.0);
	mat4 drawSnowFlake = scale_Matrix*rotate_Matrix*trans_Matrix;

	gl_Position = drop_transMatrix*xPosition_transMatrix*drop_rotateMatrix*drawSnowFlake*position; 
};