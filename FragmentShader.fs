#version 450 core

in vec3 picolor;

out vec4 pixel;

uniform sampler2D tex;

void main(){
	pixel = vec4(picolor.rgb, 1.0); 
}