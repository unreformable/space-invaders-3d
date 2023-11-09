#version 450 core

in vec3 fNormal;

out vec4 FragColor;

void main()
{
   vec3 light_col = vec3(0.9);
   vec3 light_pos = vec3(0, 3000, 1500);
   vec3 dir_to_light = normalize(light_pos);

   float diff = max(dot(fNormal, dir_to_light), 0.0);
   vec3 diffuse = diff * light_col;

   FragColor = vec4(diffuse, 1.0);
}