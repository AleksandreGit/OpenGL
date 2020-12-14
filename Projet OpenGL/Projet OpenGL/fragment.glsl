#version 330 core
// On renvoie une couleur
out vec4 FragColor;
in vec4 color;
in vec3 position;

void main()
{
	//FragColor = color;
	FragColor = vec4(position, 1.0);
}