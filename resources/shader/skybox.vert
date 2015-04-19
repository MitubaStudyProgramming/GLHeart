#version 330 core

layout(location = 0) in vec3 Position;

out vec3 TexCoord;

uniform mat4 uWVP;

void main(){
	vec4 wvpPos  = uWVP * vec4(Position, 1.0);
	gl_Position = wvpPos.xyww;
	TexCoord = Position;
}