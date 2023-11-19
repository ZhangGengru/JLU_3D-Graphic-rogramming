#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vColor;
out vec3 Color;//��ƬԴ��ɫ��������������ͣ���������ȫһ��

uniform mat4 Matrix;

void main()
{
   Color = vColor;
   vec4 position = vec4(vPos, 1.0);
   gl_Position = Matrix*position;
};