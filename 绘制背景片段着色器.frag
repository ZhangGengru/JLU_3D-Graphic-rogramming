#version 330 core

out vec4 outColor;
in vec2 outTexture;

uniform sampler2D myTexture;

void main()
{
	outColor = texture(myTexture,outTexture);
	//outColor = vec4(1.0f,0.0f,0.0f,1.0f);
}