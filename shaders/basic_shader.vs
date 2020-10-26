#version 430 core

layout(location = 0) in vec2 InPos;
layout(location = 1) in vec2 InTexCoord;
layout(location = 2) in vec4 InColor;

out vec2 texCoord0;
out vec4 color0;

void main()
{	
	gl_Position = vec4(vec3(InPos.x - 1.0, 1.0 - InPos.y, 0), 1.0);
	texCoord0 = InTexCoord;
	color0 = InColor;
}
