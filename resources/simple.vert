#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 TexCoord;

out vec2 TexCoord0;

uniform mat4 uWorldMatrix;
uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;

void main(){
	   gl_Position = uProjectionMatrix * uViewMatrix * uWorldMatrix * vec4(Position, 1.0);
	   TexCoord0 = TexCoord.xy;
}
