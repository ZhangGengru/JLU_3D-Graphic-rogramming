#version 330 core
layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vColor;
layout (location = 2) in vec2 vTexture;

out vec3 tColor;
out vec2 tTexture;
void main(){
	gl_Position = vec4(vPosition,1.0);
	tColor = vColor;
	tTexture = vTexture;
}