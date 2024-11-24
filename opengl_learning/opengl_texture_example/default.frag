#version 330 core

in vec3 color;
in vec2 TextCoords;
out vec4 FragColor;

uniform sampler2D texture1; //uniform for texture?
void main()
{	 
 FragColor = texture(texture1,TextCoords);

}