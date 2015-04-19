#version 330 core

uniform samplerCube Cubemap;

in vec3 TexCoord;
out vec4 FragColor;

void main(){
    FragColor = texture(Cubemap, TexCoord);
}