#version 330 core

layout(location = 0) in vec3 Position;

uniform mat4 uMVP;

void main(){
	gl_Position = uMVP * vec4(Position, 1.0);
}