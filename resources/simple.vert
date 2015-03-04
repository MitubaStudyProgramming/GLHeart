#version 330 core

layout(location = 0) in vec3 Position;

out vec4 Color;

uniform mat4 uWorldMatrix;
uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;

void main(){
	   gl_Position = uProjectionMatrix * uViewMatrix * uWorldMatrix * vec4(Position, 1.0);
	   Color = vec4(clamp(Position, 0.0, 1.0), 1.0);
}
