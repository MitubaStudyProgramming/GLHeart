#version 330

uniform sampler2D uBase;

in vec2 vTexCoord;
out vec4 FragColor;

void main()
{
    //float Depth = texture2D(uBase, vTexCoord).x;
    //Depth = 1.0 - (1.0 - Depth) * 25.0;
    FragColor = texture2D(uBase, vTexCoord);
}