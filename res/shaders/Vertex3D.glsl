#version 460 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;
layout (location = 2) in vec2 a_TexCoords;
//layout (location = 2) in vec3 a_Normal;

out vec2 v_TexCoords;
out vec4 v_Color;

uniform mat4 u_CameraMatrix;
uniform vec4 u_Color;

void main()
{
	gl_Position = u_CameraMatrix * vec4(a_Position, 1.0);
	v_TexCoords = a_TexCoords;
	v_Color = a_Color;
}