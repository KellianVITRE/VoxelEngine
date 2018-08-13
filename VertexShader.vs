#version 450 core

layout (location=0) in vec3 position;
layout (location=1) in vec3 normal;
layout (location=2) in vec3 color;
uniform mat4 MVP;

out vec3 picolor;

void main(){
	picolor = color;
	vec4 pos = vec4(position.xyz, 1.0);
	gl_Position = MVP * pos;
}