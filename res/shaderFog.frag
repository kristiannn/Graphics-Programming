#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  

uniform float zValue;  
uniform vec3 objectColor;
uniform vec3 fogColor;
uniform float maxDist; //fog max distance
uniform float minDist; //fog min distance


void main()
{
    float dist = abs( zValue );
	float fogFactor = (maxDist - dist) / (maxDist - minDist);
	fogFactor = clamp( fogFactor, 0.0, 1.0 );
	
	vec3 color = mix( fogColor, objectColor, fogFactor);
    FragColor = vec4(color, 1.0);
} 