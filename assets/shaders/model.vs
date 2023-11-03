#version 450 core

layout(location = 0) in vec3 vPos;

uniform mat4 uWorld;
uniform mat4 uView;
uniform mat4 uProj;

void main()
{
   gl_Position = uProj * uView * uWorld * vec4(vPos, 1.0);
}