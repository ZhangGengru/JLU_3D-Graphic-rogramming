#version 330 core
layout (location = 0) in vec3 vPos;
//layout (location = 1) in vec3 vColor;

out vec3 Color;//和片源着色器的输入变量类型，变量名完全一致

void main()
{
   //Color = vColor;
   gl_Position = vec4(vPos, 1.0);
   
};