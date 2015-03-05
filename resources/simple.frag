#version 330 core

uniform sampler2D Base;

in vec2 TexCoord0;
out vec4 color;

void main(){
    color = texture2D(Base, TexCoord0);
}