// declare version, and OpenGL mode
#version 330 core

// Take a vec3 as input
layout (location = 0) in vec3 aPos; 
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTextCoord;

out vec4 color;
out vec3 position;
out vec2 textCoord;

uniform float offset;

void main()
{
	// output of the vertex shader --> assigning to the predefined variable gl_Position
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	// UPSIDE DOWN triangle
	//gl_Position = vec4(aPos.x + offset, -aPos.y, aPos.z, 1.0);
	color = vec4(aColor, 1.0);
	position = aPos;
	textCoord = aTextCoord;
}