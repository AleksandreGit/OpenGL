// declare version, and OpenGL mode
#version 330 core

// Take a vec3 as input
layout (location = 0) in vec3 aPos; 

void main()
{
	// output of the vertex shader --> assigning to the predefined variable gl_Position
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}