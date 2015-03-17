#version 330 core

uniform float Ka;
uniform float Kd;
uniform float Ks;
uniform float Shininess;

uniform vec3 uLightPosition;
uniform vec3 uCameraPosition;

uniform sampler2D uBase;

in vec2 vTexCoord0;
in vec3 vNormalW;
in vec3 vVertexPositionW;
out vec4 FragColor;

void main(){
	vec4 texColor = texture2D(uBase, vTexCoord0);

	// ambient
	vec4 ambient = texColor * Ka;

	// diffuse
	vec3 lightDir = normalize(uLightPosition - vVertexPositionW);
	vec4 diffuse = texColor * max(dot(lightDir, vNormalW), 0.0) * Kd;

	// specular
	vec3 eyeDir = normalize(uCameraPosition - vVertexPositionW);
	vec3 reflectDir = reflect(-lightDir, vNormalW);
	vec4 specular = texColor * pow(max(dot(eyeDir, reflectDir), 0.0), Shininess) * Ks;

    FragColor = (ambient * 1.0001) + (diffuse * 1.0001) + (specular * 1.0001);
    //FragColor = vec4(vec3(0.5, 0.5, 0.5) + vNormalW * 0.5, 1.0);
    //FragColor = vec4(vVertexPositionW, 1.0);
    //FragColor = texColor;
}