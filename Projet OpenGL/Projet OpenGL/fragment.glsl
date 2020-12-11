#version 330 core
// On renvoie une couleur
out vec4 FragColor;
in vec4 color;

void main()
{
	FragColor = color;
}