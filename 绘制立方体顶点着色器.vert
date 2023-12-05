#version 330 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 inTexture;

out vec2 outTexture;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 rotation;
//uniform mat4 translation;//不同位置的平移

void main()
{
	gl_Position = projection*view*model*rotation*vec4(inPosition,1.0);
	outTexture = inTexture;
}
