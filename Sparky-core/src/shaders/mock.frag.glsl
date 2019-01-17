#version 330 core

out vec4 deColor;
in vec4 theColor;

void main()
{
	deColor = theColor;
};