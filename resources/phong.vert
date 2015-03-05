#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTexCoord;
//layout(location = 2) in vec3 aNormal;

uniform mat4 uWorldMatrix;
uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;

out vec2 vTexCoord0;
//out vec3 vNormalW;
//out vec3 vVertexPositionW;

void main(){
	   gl_Position = uProjectionMatrix * uViewMatrix * uWorldMatrix * vec4(aPosition, 1.0);
	   vTexCoord0 = aTexCoord.xy;
	   //vNormalW = (uWorldMatrix * vec4(aNormal, 0.0)).xyz;
	   //vVertexPositionW = (uWorldMatrix * vec4(aPosition, 1.0)).xyz;
}
