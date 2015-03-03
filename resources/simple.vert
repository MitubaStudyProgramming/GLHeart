#version 330 core

layout(location = 0) in vec3 Position;
uniform float gScale;

void main(){
	   gl_Position = vec4(gScale * Position, 1.0);
}
