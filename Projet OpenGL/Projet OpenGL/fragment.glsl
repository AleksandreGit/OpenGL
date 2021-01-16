#version 330 core
// On renvoie une couleur
out vec4 FragColor;
in vec4 color;
in vec3 position;
in vec2 textCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
//uniform float warp;

void main()
{
	//FragColor = color;
	//FragColor = vec4(position, 1.0);
	//FragColor = mix(texture(texture1, textCoord), texture(texture2, textCoord), 0.5);
	FragColor = texture(texture1, textCoord);
}